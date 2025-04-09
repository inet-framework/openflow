#include "openflow/kandoo/KandooAgent.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "algorithm"
#include "string"

#define MSGKIND_KNCONNECT 1404

namespace openflow{

Define_Module(KandooAgent);

KandooAgent::KandooAgent(){

}

KandooAgent::~KandooAgent(){
    for(auto&& pair : socketMap){
        delete pair.second;
    }
    socketMap.clear();
}

void KandooAgent::initialize(){
    AbstractTCPControllerApp::initialize();


    //init socket to synchronizer
    const char *localAddress = par("localAddress");
    int localPort = par("localPort");
    isRootController = par("isRootController");


    if(isRootController){
        socket.setOutputGate(gate("tcpOut"));
        socket.setDataTransferMode(TCP_TRANSFER_OBJECT);
        socket.bind(localAddress[0] ? L3Address(localAddress) : L3Address(), par("connectPortRootController"));
        socket.listen();
    } else {
        socket.bind(localAddress[0] ? L3Address(localAddress) : L3Address(), localPort);
        socket.setOutputGate(gate("tcpOut"));
        socket.setDataTransferMode(TCP_TRANSFER_OBJECT);

        cMessage *initiateConnection = new cMessage("initiateConnection");
        initiateConnection->setKind(MSGKIND_KNCONNECT);
        scheduleAt(par("connectAt"), initiateConnection);
    }

    //register signals
    kandooEventSignalId =registerSignal("KandooEvent");



}

void KandooAgent::handleMessage(cMessage *msg){
    AbstractTCPControllerApp::handleMessage(msg);

    if (msg->isSelfMessage()){
        if (msg->getKind()== MSGKIND_KNCONNECT){
            //init socket to synchronizer
            const char *connectAddressRootController = par("connectAddressRootController");
            int connectPort = par("connectPortRootController");
            socket.connect(L3AddressResolver().resolve(connectAddressRootController), connectPort);
            delete msg;
        }
    }

}



void KandooAgent::processQueuedMsg(cMessage *msg){

    if(isRootController){
        if(dynamic_cast<KN_Packet *>(msg) != NULL){
            KN_Packet *castMsg = (KN_Packet *)msg;

            cObject *payload = castMsg->getKnEntry().payload;
            if (payload && payload->isOwnedObject())
                take(static_cast<cOwnedObject *>(payload));

            bool found = false;
            std::list<SwitchControllerMapping>::iterator iter;
            for(iter = switchControllerMapping.begin(); iter != switchControllerMapping.end();iter++){
                if(strcmp(iter->switchId.c_str(),castMsg->getKnEntry().srcSwitch.c_str())==0){
                    found = true;
                    break;
                }
            }
            if(!found){
                SwitchControllerMapping mapping = SwitchControllerMapping();
                mapping.controllerId = castMsg->getKnEntry().srcController;
                mapping.switchId = castMsg->getKnEntry().srcSwitch;
                mapping.socket = findSocketFor(castMsg);

                switchControllerMapping.push_front(mapping);
            }

            handleKandooPacket(castMsg);
            delete payload;
        } else {
            TCPSocket *socket = findSocketFor(msg);
            if(!socket){
                socket = new TCPSocket(msg);
                socket->setOutputGate(gate("tcpOut"));
                ASSERT(socketMap.find(socket->getConnectionId())==socketMap.end());
                socketMap[socket->getConnectionId()] = socket;
            }
        }
        delete msg;
    } else {
         //check if message was received via our socket
         if(socket.belongsToSocket(msg)){
             if(msg->getKind() == TCP_I_ESTABLISHED){
                 socket.processMessage(msg);
             } else {
                 if (dynamic_cast<KN_Packet *>(msg) != NULL) {
                     KN_Packet *castMsg = (KN_Packet *)msg;
                     cObject *payload = castMsg->getKnEntry().payload;
                     if (payload && payload->isOwnedObject())
                         take(static_cast<cOwnedObject *>(payload));
                     handleKandooPacket(castMsg);
                     delete payload;
                 }

                 delete msg;
             }
         } else {
             delete msg;
         }
    }

}


bool KandooAgent::getIsRootController(){
    return isRootController;
}


void KandooAgent::sendRequest(KandooEntry entry){
    Enter_Method_Silent();
    KN_Packet * knpck = new KN_Packet("KN Req");
    knpck->setKnEntry(entry);
    knpck->setByteLength(1);
    knpck->setKind(TCP_C_SEND);

    socket.send(knpck);
}

void KandooAgent::sendReply(KN_Packet * knpck,KandooEntry entry){
    Enter_Method_Silent();

    KN_Packet * knrep = new KN_Packet("KN Rep");
    knrep->setKnEntry(entry);
    knrep->setByteLength(1);
    knrep->setKind(TCP_C_SEND);

    TCPSocket * tempSocket = findSocketFor(knpck);
    tempSocket->send(knrep);
}

void KandooAgent::sendReplyToSwitchAuthoritive(std::string switchId, KandooEntry entry){
    Enter_Method_Silent();

    KN_Packet * knrep = new KN_Packet("KN Rep");
    knrep->setKnEntry(entry);
    knrep->setByteLength(1);
    knrep->setKind(TCP_C_SEND);

    TCPSocket * tempSocket = NULL;
    std::list<SwitchControllerMapping>::iterator iter;
    for(iter = switchControllerMapping.begin(); iter != switchControllerMapping.end();iter++){
        if(strcmp(iter->switchId.c_str(),switchId.c_str())==0){
            tempSocket = iter->socket;
            break;
        }
    }

    if(tempSocket != NULL){
        tempSocket->send(knrep);
    }

}


void KandooAgent::handleKandooPacket(KN_Packet * knpck){
    emit(kandooEventSignalId,knpck);
}

TCPSocket * KandooAgent::findSocketFor(cMessage *msg) {
    TCPCommand *ind = dynamic_cast<TCPCommand *>(msg->getControlInfo());
    if (!ind)
        throw cRuntimeError("SocketMap: findSocketFor(): no TCPCommand control info in message (not from TCP?)");

    std::map<int,TCPSocket*>::iterator i = socketMap.find(ind->getConnId());
    ASSERT(i==socketMap.end() || i->first==i->second->getConnectionId());
    return (i==socketMap.end()) ? NULL : i->second;
}

} /*end namespace openflow*/
