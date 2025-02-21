#include "openflow/kandoo/KandooAgent.h"
#include "inet/common/socket/SocketTag_m.h"
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

void KandooAgent::initialize(int stage){
    AbstractTCPControllerApp::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        //init socket to synchronizer
        isRootController = par("isRootController");
        //register signals
        kandooEventSignalId =registerSignal("KandooEvent");
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        const char *localAddress = par("localAddress");
        int localPort = par("localPort");

        if(isRootController){
            socket.setOutputGate(gate("socketOut"));
            socket.setCallback(this);
            socket.bind(localAddress[0] ? L3Address(localAddress) : L3Address(), par("connectPortRootController"));
            socket.listen();
        } else {
            socket.bind(localAddress[0] ? L3Address(localAddress) : L3Address(), localPort);
            socket.setOutputGate(gate("socketOut"));
        }
    }
}

void KandooAgent::handleStartOperation(LifecycleOperation *operation) {
    if (!isRootController) {
        cMessage *initiateConnection = new cMessage("initiateConnection");
        initiateConnection->setKind(MSGKIND_KNCONNECT);
        simtime_t connectAt = par("connectAt");
        simtime_t start = std::max(simTime(), connectAt);
        scheduleAt(start, initiateConnection);
    }
}

void KandooAgent::processSelfMessage(cMessage *msg){

    if (msg->getKind()== MSGKIND_KNCONNECT) {
        //init socket to synchronizer
        const char *connectAddressRootController = par("connectAddressRootController");
        int connectPort = par("connectPortRootController");
        socket.connect(L3AddressResolver().resolve(connectAddressRootController), connectPort);
        delete msg;
    }
    else {
        AbstractTCPControllerApp::processSelfMessage(msg);
    }
}

void KandooAgent::processQueuedMsg(cMessage *msg)
{
    TcpSocket *activeSocket = findSocketFor(msg);
    if (activeSocket) {
        activeSocket->processMessage(msg);
    }
    else {
        auto& tags = check_and_cast<ITaggedObject *>(msg)->getTags();
        int socketId = tags.getTag<SocketInd>()->getSocketId();
        throw cRuntimeError("model error: no socket found for msg '%s' with socketId %d", msg->getName(), socketId);
    }
}

void KandooAgent::socketDataArrived(TcpSocket *socket)
{
#if (INET_VERSION > 0x405)
    auto queue = socket->getReadBuffer();
#else
    auto queue = socket->getReceiveQueue();
#endif

    while (queue->has<KN_Packet>()) {
        auto header = queue->pop<KN_Packet>();
        auto packet = new Packet();
        packet->insertAtFront(header);
        packet->addTag<SocketInd>()->setSocketId(socket->getSocketId());
        Action action(ACTION_DATA, packet);
        if (!busy)
            startProcessingMsg(action);
        else
            msgList.push_back(action);
    }
}

void KandooAgent::socketAvailable(TcpSocket *listenerSocket, TcpAvailableInfo *availableInfo)
{
    ASSERT(listenerSocket == &socket);

    auto newSocketId = availableInfo->getNewSocketId();
    TcpSocket *newSocket = new TcpSocket(availableInfo);
    newSocket->setOutputGate(gate("socketOut"));
    newSocket->setCallback(this);
    socketMap[newSocketId] = newSocket;
    socket.accept(newSocketId);
}

void KandooAgent::processPacketFromTcp(Packet *msg)
{
    if(isRootController){
        auto castMsg = msg->peekAtFront<KN_Packet>();
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
            mapping.socket = findSocketFor(msg);

            switchControllerMapping.push_front(mapping);
        }
    }

    auto castAux =  msg->removeAtFront<KN_Packet>();
    cObject *payload = castAux->getKnEntryForUpdate().payload;
    if (payload && payload->isOwnedObject())
        take(static_cast<cOwnedObject *>(payload));
    msg->insertAtFront(castAux);
    handleKandooPacket(msg);
    delete payload;
    delete msg;
}

bool KandooAgent::getIsRootController(){
    return isRootController;
}


void KandooAgent::sendRequest(KandooEntry entry){
    Enter_Method_Silent();

    auto knpck = makeShared<KN_Packet>();
    auto pkt = new Packet("KN Req");
    knpck->setKnEntry(entry);
    knpck->setChunkLength(B(1));
    pkt->setKind(TCP_C_SEND);
    pkt->insertAtFront(knpck);
    socket.send(pkt);
}

void KandooAgent::sendReply(Packet * pktIn, KandooEntry entry){
    Enter_Method_Silent();

    auto knpck = pktIn->peekAtFront<KN_Packet>();
    auto knrep = makeShared<KN_Packet>();
    auto pkt = new Packet("KN Rep");
    knrep->setKnEntry(entry);
    knrep->setChunkLength(B(1));
    pkt->setKind(TCP_C_SEND);
    pkt->insertAtFront(knrep);

    TcpSocket * tempSocket = findSocketFor(pktIn);
    tempSocket->send(pkt);
}

void KandooAgent::sendReplyToSwitchAuthoritive(std::string switchId, KandooEntry entry){
    Enter_Method_Silent();

    auto knrep = makeShared<KN_Packet>();
    auto pkt = new Packet("KN Rep");
    knrep->setKnEntry(entry);
    knrep->setChunkLength(B(1));
    pkt->setKind(TCP_C_SEND);
    pkt->insertAtFront(knrep);

    TcpSocket * tempSocket = NULL;
    std::list<SwitchControllerMapping>::iterator iter;
    for(iter = switchControllerMapping.begin(); iter != switchControllerMapping.end(); ++iter){
        if(strcmp(iter->switchId.c_str(),switchId.c_str())==0){
            tempSocket = iter->socket;
            break;
        }
    }

    if(tempSocket != NULL){
        tempSocket->send(pkt);
    }

}


void KandooAgent::handleKandooPacket(Packet * pktIn){
    auto knpck = pktIn->peekAtFront<KN_Packet>();
    emit(kandooEventSignalId,pktIn);
}

TcpSocket * KandooAgent::findSocketFor(cMessage *msg) {
    if (socket.belongsToSocket(msg))
        return &socket;
    auto& tags = check_and_cast<ITaggedObject *>(msg)->getTags();
    auto tag = tags.findTag<SocketInd>();
    if (tag == nullptr)
        throw cRuntimeError("SocketMap: findSocketFor(): no SocketInd (not from TCP?)");

    auto i = socketMap.find(tag->getSocketId());
    ASSERT(i==socketMap.end() || i->first==i->second->getSocketId());
    return (i==socketMap.end()) ? nullptr : i->second;
}

} /*end namespace openflow*/
