#include <KandooAgent.h>
#include "IPvXAddressResolver.h"
#include "Switch_Info.h"
#include "algorithm"
#include "string"

#define MSGKIND_KNCONNECT 1404

Define_Module(KandooAgent);

KandooAgent::KandooAgent(){

}

KandooAgent::~KandooAgent(){

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
        socket.bind(localAddress[0] ? IPvXAddress(localAddress) : IPvXAddress(), par("connectPortRootController"));
        socket.listen();
    } else {
        socket.bind(localAddress[0] ? IPvXAddress(localAddress) : IPvXAddress(), localPort);
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
            socket.connect(IPvXAddressResolver().resolve(connectAddressRootController), connectPort);
            delete msg;
        }
    }

}



void KandooAgent::processQueuedMsg(cMessage *msg){

    if(isRootController){
        if(dynamic_cast<KN_Packet *>(msg) != NULL){
            KN_Packet *castMsg = (KN_Packet *)msg;

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
            delete castMsg->getKnEntry().payload;
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
                     handleKandooPacket(castMsg);
                     delete castMsg->getKnEntry().payload;
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





