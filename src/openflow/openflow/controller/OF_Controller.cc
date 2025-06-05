#include <omnetpp.h>
#include "openflow/openflow/controller/OF_Controller.h"

#include "inet/applications/tcpapp/GenericAppMsg_m.h"
#include "openflow/openflow/protocol/OpenFlow.h"
#include "openflow/messages/Open_Flow_Message_m.h"
#include "openflow/messages/OFP_Packet_Out_m.h"
#include "inet/transportlayer/contract/tcp/TcpCommand_m.h"
#include "openflow/messages/OFP_Flow_Mod_m.h"
#include "openflow/messages/OFP_Features_Request_m.h"
#include "openflow/messages/OFP_Features_Reply_m.h"
#include "inet/transportlayer/tcp/TcpConnection.h"
#include "openflow/messages/OFP_Initialize_Handshake_m.h"
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "inet/common/socket/SocketTag_m.h"


using namespace std;

#define MSGKIND_BOOTED 100
#define MSGKIND_EVENT  101
#define MSGKIND_DATA   102

namespace openflow{

Define_Module(OF_Controller);

simsignal_t OF_Controller::PacketInSignalId =registerSignal("PacketIn");
simsignal_t OF_Controller::PacketOutSignalId =registerSignal("PacketOut");
simsignal_t OF_Controller::PacketHelloSignalId =registerSignal("PacketHello");
simsignal_t OF_Controller::PacketFeatureRequestSignalId = registerSignal("PacketFeatureRequest");
simsignal_t OF_Controller::PacketFeatureReplySignalId = registerSignal("PacketFeatureReply");
simsignal_t OF_Controller::PacketExperimenterSignalId = registerSignal("PacketExperimenter");
simsignal_t OF_Controller::BootedSignalId = registerSignal("Booted");

OF_Controller::OF_Controller(){

}

OF_Controller::~OF_Controller(){
    for(auto&& msg : this->msgList) {
      delete msg.msg;
    }
    this->msgList.clear();
}

void OF_Controller::initialize(int stage){
    //register signals
    OperationalBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {

    //stats
        queueSize = registerSignal("queueSize");
        waitingTime = registerSignal("waitingTime");
        numPacketIn=0;
        lastQueueSize =0;
        lastChangeTime=0.0;

    //parameters
        serviceTime = par("serviceTime");
        busy = false;
    parallelProcessing = par("parallelProcessing").boolValue();

    // TCP socket; listen on incoming connections
        const char *address = par("address");
        int port = par("port");
        socket.setOutputGate(gate("socketOut"));
        socket.setCallback(this);
        // socket.setDataTransferMode(TCP_TRANSFER_OBJECT);
        socket.bind(address[0] ? L3Address(address) : L3Address(), port);


    }
    else if (stage == INITSTAGE_APPLICATION_LAYER)
        socket.listen();
}


void OF_Controller::handleStartOperation(LifecycleOperation *operation)
{
    //schedule booted message
    cMessage *booted = new cMessage("Booted");
    booted->setKind(MSGKIND_BOOTED);
    scheduleAt(simTime() + par("bootTime").doubleValue(), booted);
}


void OF_Controller::sendPacket(TcpSocket *socket, Packet *msg) {
    Enter_Method_Silent();
    for(auto elem : switchesList) {
        if (elem.getSocket() == socket) {
            take(msg);
            socket->send(msg);
        }

    }
}

void OF_Controller::startProcessingMsg(Action& action)
{
    busy = true;
    cMessage *msg = action.msg;
    cMessage *event = new cMessage("event");
    event->setKind(action.kind);
    event->setContextPointer(msg);
    EV_DEBUG << "Start processing of message " << msg->getName() << endl;
    scheduleAt(simTime()+serviceTime, event);
}

void OF_Controller::handleMessageWhenUp(cMessage *msg){
    if (msg->isSelfMessage()) {
        if (msg->getKind()==MSGKIND_BOOTED){
            // TODO open the listener socket (move here from initialize() )
            booted = true;
            emit(BootedSignalId, this);
        }
        else if (msg->getKind() == MSGKIND_EVENT || msg->getKind() == MSGKIND_DATA){
            //This is message which has been scheduled due to service time
            //Get the Original message
            cMessage *data_msg = (cMessage *) msg->getContextPointer();
            EV_DEBUG << "End of processing message " << data_msg->getName() << endl;
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
            calcAvgQueueSize(msgList.size());
            emit(queueSize,static_cast<unsigned long>(msgList.size()));
        }
        //delete the msg for efficiency
        delete msg;
    }else if (this->booted){
        if (msg->getKind() == TCP_I_DATA || msg->getKind() == TCP_I_URGENT_DATA || msg->getKind() == TCP_I_AVAILABLE)
            processQueuedMsg(msg);
        else {
            //implement service time
            Action action(MSGKIND_EVENT, msg);
            if (!parallelProcessing && busy) {
                msgList.push_back(action);
            }else{
                startProcessingMsg(action);
            }
        }

        calcAvgQueueSize(msgList.size());
        emit(queueSize,static_cast<unsigned long>(msgList.size()));
    } else {
        // this is not a self message and we are not yet booted
        // ignore it.
        delete msg;
    }
}

void OF_Controller::calcAvgQueueSize(int size){
    if(lastQueueSize != size) {
        double timeDiff = simTime().dbl() - lastChangeTime;
        if(avgQueueSize.count(floor(simTime().dbl())) <=0){
            avgQueueSize.insert(pair<int,double>(floor(simTime().dbl()),lastQueueSize*timeDiff));
        }
        else {
            avgQueueSize[floor(simTime().dbl())] += lastQueueSize*timeDiff;
        }
        lastChangeTime = simTime().dbl();
        lastQueueSize = size;
    }
}



void OF_Controller::socketEstablished(TcpSocket *socket)
{
}

void OF_Controller::socketAvailable(TcpSocket *listenerSocket, TcpAvailableInfo *availableInfo)
{
    ASSERT(listenerSocket == &socket);

    //TODO is it good? AVAILABLE for existing socket?
    int sockId = listenerSocket->getSocketId();
    for(auto elem : switchesList) {
        if(elem.getSocket()->getSocketId() == sockId){
            elem.getSocket()->accept(availableInfo->getNewSocketId());
            return;
        }
    }

    TcpSocket *newSocket = new TcpSocket(availableInfo);

    newSocket->setOutputGate(gate("socketOut"));
    newSocket->setCallback(this);
    Switch_Info swInfo = Switch_Info();
    swInfo.setSocket(newSocket);
    swInfo.setConnId(newSocket->getSocketId());
    swInfo.setMacAddress("");
    swInfo.setNumOfPorts(-1);
    swInfo.setVersion(-1);
    switchesList.push_back(swInfo);
    listenerSocket->accept(availableInfo->getNewSocketId());
}

void OF_Controller::socketDataArrived(TcpSocket *socket)
{
#if (INET_VERSION > 0x405)
    auto queue = socket->getReadBuffer();
#else
    auto queue = socket->getReceiveQueue();
#endif

    while (queue->has<Open_Flow_Message>()) {
        auto header = queue->peek<Open_Flow_Message>();
        b length = B(header->getHeader().length);
        ASSERT(length >= header->getChunkLength());
        if (queue->getLength() >= length) {
            auto data = queue->pop(length);
            auto packet = new Packet();
            packet->insertAtFront(data);
            packet->addTag<SocketInd>()->setSocketId(socket->getSocketId());
            Action action(MSGKIND_DATA, packet);
            if (!busy || parallelProcessing)
                startProcessingMsg(action);
            else
                msgList.push_back(action);
        }
        else
            break;
    }
}

void OF_Controller::socketPeerClosed(TcpSocket *socket)
{
}

void OF_Controller::socketClosed(TcpSocket *socket)
{
}

void OF_Controller::socketFailure(TcpSocket *socket, int code)
{
}


void OF_Controller::processPacketFromTcp(Packet *pkt)
{
    const auto of_msg = pkt->peekAtFront<Open_Flow_Message>();
    ofp_type type = (ofp_type)of_msg->getHeader().type;
    switch (type) {
        case OFPT_FEATURES_REPLY:
            handleFeaturesReply(pkt);
            break;
        case OFPT_HELLO: {
            Switch_Info *switchInfo = CHK(findSwitchInfoFor(pkt));
            switchInfo->setVersion(of_msg->getHeader().version);
            sendHello(pkt);
            sendFeatureRequest(pkt);
            break;
        }
        case OFPT_PACKET_IN:
            EV << "packet-in message from switch\n";
            handlePacketIn(pkt);
            break;
        case OFPT_VENDOR:
            // the controller apps might want to implement vendor specific features so forward them.
            handleExperimenter(pkt);
            break;
        default:
            break;
    }
    delete pkt;
}

void OF_Controller::processQueuedMsg(cMessage *msg)
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

void OF_Controller::sendHello(Packet *pkt){
    //Open_Flow_Message *msg
    auto hello = makeShared<OFP_Hello>();
    auto pktHello = new Packet("Hello");
    hello->getHeaderForUpdate().version = OFP_VERSION;
    hello->getHeaderForUpdate().type = OFPT_HELLO;
    hello->setChunkLength(B(8));
    hello->getHeaderForUpdate().length = hello->getChunkLength().get<B>() + pktHello->getByteLength();
    pktHello->setKind(TCP_C_SEND);
    pktHello->insertAtFront(hello);

    emit(PacketHelloSignalId, pktHello);
    auto socket = findSocketFor(pkt);
    socket->send(pktHello);
}

void OF_Controller::sendFeatureRequest(Packet *pkt){
    auto featuresRequest = makeShared<OFP_Features_Request>();
    auto pktFeauresReq = new Packet("FeaturesRequest");
    featuresRequest->getHeaderForUpdate().version = OFP_VERSION;
    featuresRequest->getHeaderForUpdate().type = OFPT_FEATURES_REQUEST;
    featuresRequest->setChunkLength(B(8));
    featuresRequest->getHeaderForUpdate().length = featuresRequest->getChunkLength().get<B>() + pktFeauresReq->getByteLength();
    pktFeauresReq->setKind(TCP_C_SEND);
    pktFeauresReq->insertAtFront(featuresRequest);

    emit(PacketFeatureRequestSignalId,pktFeauresReq);
    auto socket = findSocketFor(pkt);
    socket->send(pktFeauresReq);
}

void OF_Controller::handleFeaturesReply(Packet *pkt){
    EV << "OFA_controller::handleFeaturesReply" << endl;
    auto swInfo= findSwitchInfoFor(pkt);

    auto of_msg = pkt->peekAtFront<Open_Flow_Message>();
    auto castMsg = dynamicPtrCast<const OFP_Features_Reply>(of_msg);

    if(castMsg != nullptr){
        swInfo->setMacAddress(castMsg->getDatapath_id());
        swInfo->setNumOfPorts(castMsg->getPortsArraySize());
        for (int i = 0; i < castMsg->getPortsArraySize(); i++)
        swInfo->setSwitchPortsIndexId(i,castMsg->getPorts(i));
        emit(PacketFeatureReplySignalId,pkt);
    }
}

void OF_Controller::handlePacketIn(Packet *pkt){
    auto of_msg = pkt->peekAtFront<Open_Flow_Message>();
    EV << "OFA_controller::handlePacketIn" << endl;
    numPacketIn++;
    emit(PacketInSignalId, pkt);
}


void OF_Controller::sendPacketOut(Packet *pkt, TcpSocket *socket){
    Enter_Method_Silent();
    take(pkt);
    auto  of_msg = pkt->peekAtFront<Open_Flow_Message>();
    EV << "OFA_controller::sendPacketOut" << endl;
    emit(PacketOutSignalId,pkt);
    socket->send(pkt);
}


void OF_Controller::handleExperimenter(Packet* pkt) {
    Enter_Method_Silent();
    take(pkt);
    auto  of_msg = pkt->peekAtFront<Open_Flow_Message>();
    EV << "OFA_controller::handleExperimenter" << endl;
    emit(PacketExperimenterSignalId, pkt);
}


void OF_Controller::registerConnection(Indication *sockInfo) {

    auto availableInfo = check_and_cast<TcpAvailableInfo *>(sockInfo->getControlInfo());

    int sockId = sockInfo->getTag<SocketInd>()->getSocketId();
    for(auto elem : switchesList) {
        if(elem.getSocket()->getSocketId() == sockId){
            elem.getSocket()->accept(availableInfo->getNewSocketId());
            return;
        }
    }

    TcpSocket *newSocket = new TcpSocket(availableInfo);

    newSocket->setOutputGate(gate("socketOut"));
    Switch_Info swInfo = Switch_Info();
    swInfo.setSocket(newSocket);
    swInfo.setConnId(newSocket->getSocketId());
    swInfo.setMacAddress("");
    swInfo.setNumOfPorts(-1);
    swInfo.setVersion(-1);
    switchesList.push_back(swInfo);
    socket.accept(availableInfo->getNewSocketId());
}

TcpSocket *OF_Controller::findSocketFor(cMessage *msg) const
{
    auto& tags = check_and_cast<ITaggedObject *>(msg)->getTags();
    int connId = tags.getTag<SocketInd>()->getSocketId();
    for(auto i=switchesList.begin(); i != switchesList.end(); ++i) {
        if((*i).getConnId() == connId){
            return (*i).getSocket();
        }
    }
    return nullptr;
}

Switch_Info *OF_Controller::findSwitchInfoFor(cMessage *msg)
{
    auto& tags = check_and_cast<ITaggedObject *>(msg)->getTags();
    auto tag = tags.findTag<SocketInd>();
    if (tag == nullptr)
        return nullptr;
    int connId = tag->getSocketId();
    for(auto i=switchesList.begin(); i != switchesList.end(); ++i) {
        if((*i).getConnId() == connId){
            return &(*i);
        }
    }
    return nullptr;
}

TcpSocket *OF_Controller::findSocketForChassisId(std::string chassisId) const{
    for(auto i=switchesList.begin(); i != switchesList.end(); ++i) {
        if(strcmp((*i).getMacAddress().c_str(),chassisId.c_str())==0){
            return (*i).getSocket();
        }
    }
    return nullptr;
}

void OF_Controller::registerApp(AbstractControllerApp *app){
    apps.push_back(app);
}

std::vector<Switch_Info >* OF_Controller::getSwitchesList() {
    return &switchesList;
}

std::vector<AbstractControllerApp *>* OF_Controller::getAppList() {
    return &apps;
}

void OF_Controller::finish(){
    // record statistics
    recordScalar("numPacketIn", numPacketIn);
/*
    std::map<int,int>::iterator iterMap;
    for(iterMap = packetsPerSecond.begin(); iterMap != packetsPerSecond.end(); iterMap++){
        stringstream name;
        name << "packetsPerSecondAt-" << iterMap->first;
        recordScalar(name.str().c_str(),iterMap->second);
    }

    std::map<int,double>::iterator iterMap2;
    for(iterMap2 = avgQueueSize.begin(); iterMap2 != avgQueueSize.end(); iterMap2++){
        stringstream name;
        name << "avgQueueSizeAt-" << iterMap2->first;
        recordScalar(name.str().c_str(),(iterMap2->second/1.0));
    }
*/
    for(const auto &elem : packetsPerSecond){
        stringstream name;
        name << "packetsPerSecondAt-" << elem.first;
        recordScalar(name.str().c_str(), elem.second);
    }
    for(const auto &elem : avgQueueSize){
        stringstream name;
        name << "avgQueueSizeAt-" << elem.first;
        recordScalar(name.str().c_str(),(elem.second/1.0));
    }


}

} /*end namespace openflow*/

