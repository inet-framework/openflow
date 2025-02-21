#include <omnetpp.h>
#include "openflow/hyperflow/HyperFlowSynchronizer.h"
#include "openflow/messages/HF_SyncRequest_m.h"
#include "openflow/messages/HF_ReportIn_m.h"
#include "openflow/messages/HF_SyncReply_m.h"
#include "openflow/openflow/protocol/OFMatchFactory.h"
#include "inet/common/socket/SocketTag_m.h"

using namespace std;

namespace openflow{

Define_Module(HyperFlowSynchronizer);



HyperFlowSynchronizer::HyperFlowSynchronizer(){

}

HyperFlowSynchronizer::~HyperFlowSynchronizer(){
    for(auto&& msg : msgList) {
      delete msg.msg;
    }
    msgList.clear();

    for(auto&& pair : socketMap){
        delete pair.second;
    }
    socketMap.clear();
}

void HyperFlowSynchronizer::initialize(int stage){

    //stats
    OperationalBase::initialize(stage);
    if (stage == INITSTAGE_LINK_LAYER) {
        queueSize = registerSignal("queueSize");
        waitingTime = registerSignal("waitingTime");
        // TCP socket; listen on incoming connections
        const char *address = par("address");
        int port = par("port");
        socket.setCallback(this);
        socket.setOutputGate(gate("socketOut"));
        socket.bind(address[0] ? L3Address(address) : L3Address(), port);
        dataChannelSizeCache =0;

        serviceTime = par("serviceTime");
        busy=false;
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        socket.listen();
    }
}


void HyperFlowSynchronizer::startProcessingMsg(Action& action)
{
    busy = true;
    auto msg = action.msg;
    cMessage *event = new cMessage("event");
    event->setKind(action.kind);
    event->setContextPointer(msg);
    EV_DEBUG << "Start processing of message " << msg->getName() << endl;
    scheduleAt(simTime()+serviceTime, event);
}

void HyperFlowSynchronizer::handleMessageWhenUp(cMessage *msg){
    if(msg->isSelfMessage()){
        //This is message which has been scheduled due to service time
        //Get the Original message
        cMessage *data_msg = (cMessage *) msg->getContextPointer();
        emit(waitingTime,(simTime()-data_msg->getArrivalTime()-serviceTime));
        if (msg->getKind() == MSGKIND_EVENT)
            processQueuedMsg(data_msg);
        else if (msg->getKind() == MSGKIND_DATA)
            processPacketFromTcp(check_and_cast<Packet *>(data_msg));
        else
            throw cRuntimeError("model error");

        //Trigger next service time
        if (msgList.empty()){
            busy = false;
        } else {
            Action msgfromlist = msgList.front();
            msgList.pop_front();
            startProcessingMsg(msgfromlist);
        }

        //delete the msg for efficiency
        delete msg;
    } else {
        if (msg->getKind() == TCP_I_DATA || msg->getKind() == TCP_I_URGENT_DATA || msg->getKind() == TCP_I_AVAILABLE)
            processQueuedMsg(msg);
        else {
            Action action(MSGKIND_EVENT, msg);
            //imlement service time
            if (busy) {
                msgList.push_back(action);
            }else{
                startProcessingMsg(action);
            }
        }
        emit(queueSize,static_cast<unsigned long>(msgList.size()));
    }
}

void HyperFlowSynchronizer::handleChangeNotification(Packet * pkt){
    auto msg = pkt->peekAtFront<HF_ChangeNotification>();

    dataChannel.push_front(msg->getEntry());
    dataChannelSizeCache++;
}

void HyperFlowSynchronizer::handleSyncRequest(Packet *pkt){
    //return syncreply

    auto msg = pkt->peekAtFront<HF_SyncRequest>();

    TcpSocket *socket = findSocketFor(pkt);

    auto reply = makeShared<HF_SyncReply>();
    //HF_SyncReply * reply = new HF_SyncReply("SyncReply");
    auto pktReply = new Packet("SyncReply");

    //create control channel
    std::list<ControlChannelEntry> tempControlChannel = std::list<ControlChannelEntry>();
    SimTime lastValidTime = simTime()-par("aliveInterval");

    for(auto iterControl=controlChannel.begin();iterControl!=controlChannel.end(); ) {
        if((*iterControl).time >= lastValidTime){
           tempControlChannel.push_back(*iterControl);
           ++iterControl;
        } else {
            iterControl = controlChannel.erase(iterControl);
        }
    }

    reply->setControlChannel(tempControlChannel);

    //copy only the relevant parts of the datachannel
    std::list<DataChannelEntry> tempDataChannel = std::list<DataChannelEntry>();
    std::list<DataChannelEntry>::iterator iterData;
    int counter = dataChannelSizeCache - msg->getLastSyncCounter();
    for(iterData=dataChannel.begin();counter != 0 && iterData != dataChannel.end(); ++iterData){
        counter--;
        tempDataChannel.push_back(*iterData);
    }
    reply->setDataChannel(tempDataChannel);
    reply->setChunkLength(B(sizeof(controlChannel)+sizeof(tempDataChannel)));
    //reply->setByteLength(sizeof(controlChannel)+sizeof(tempDataChannel));
    pktReply->insertAtFront(reply);
    pktReply->setKind(TCP_C_SEND);
    socket->send(pktReply);
}


void HyperFlowSynchronizer::handleReportIn(Packet * pkt){
    //store to datachannel

    auto msg = pkt->peekAtFront<HF_ReportIn>();
    ControlChannelEntry entry = ControlChannelEntry();
    entry.switches= std::list<Switch_Info *>(msg->getSwitchInfoList());
    entry.controllerId = msg->getControllerId();
    entry.time = simTime();
    controlChannel.push_front(entry);
}


TcpSocket * HyperFlowSynchronizer::findSocketFor(cMessage *msg){

    auto& tags = check_and_cast<ITaggedObject *>(msg)->getTags();
    int connId = tags.getTag<SocketInd>()->getSocketId();
    auto i = socketMap.find(connId);
    ASSERT(i==socketMap.end() || i->first==i->second->getSocketId());
    return (i==socketMap.end()) ? nullptr : i->second;
}

void HyperFlowSynchronizer::socketEstablished(TcpSocket *socket)
{
}

void HyperFlowSynchronizer::socketAvailable(TcpSocket *listenerSocket, TcpAvailableInfo *availableInfo)
{
    ASSERT(listenerSocket == &socket);

    auto newSocketId = availableInfo->getNewSocketId();
    TcpSocket *newSocket = new TcpSocket(availableInfo);
    newSocket->setOutputGate(gate("socketOut"));
    newSocket->setCallback(this);
    socketMap[newSocketId] = newSocket;
    socket.accept(newSocketId);
}

void HyperFlowSynchronizer::socketDataArrived(TcpSocket *socket)
{
    auto queue = socket->getReadBuffer();
    while (queue->has<HF_Packet>()) {
        auto header = queue->pop<HF_Packet>();
        auto packet = new Packet();
        packet->insertAtFront(header);
        packet->addTag<SocketInd>()->setSocketId(socket->getSocketId());
        Action action(MSGKIND_DATA, packet);
        if (!busy)
            startProcessingMsg(action);
        else
            msgList.push_back(action);
    }
}

void HyperFlowSynchronizer::socketPeerClosed(TcpSocket *socket)
{
}

void HyperFlowSynchronizer::socketClosed(TcpSocket *socket)
{
}

void HyperFlowSynchronizer::socketFailure(TcpSocket *socket, int code)
{
}

void HyperFlowSynchronizer::processQueuedMsg(cMessage *msg)
{
    ISocket *sock = findSocketFor(msg);
    if (sock) {
        sock->processMessage(msg);
    }
    else if (socket.belongsToSocket(msg)) {
        socket.processMessage(msg);
    }
    else {
        auto& tags = check_and_cast<ITaggedObject *>(msg)->getTags();
        int socketId = tags.getTag<SocketInd>()->getSocketId();
        throw cRuntimeError("model error: no socket found for msg '%s' with socketId %d", msg->getName(), socketId);
    }
}

void HyperFlowSynchronizer::processPacketFromTcp(Packet * msg){
    auto chunk = msg->peekAtFront<HF_Packet>();
    if (dynamicPtrCast<const HF_ReportIn>(chunk) != nullptr) {
        handleReportIn(msg);

    } else if(dynamicPtrCast<const HF_SyncRequest>(chunk) != nullptr){
        handleSyncRequest(msg);
    } else if(dynamicPtrCast<const HF_ChangeNotification>(chunk) != nullptr){
        handleChangeNotification(msg);
    } else {
        EV << "Packet dropped: " << EV_FIELD(msg) << endl;
    }
}

} /*end namespace openflow*/

