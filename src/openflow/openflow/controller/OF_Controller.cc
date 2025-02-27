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

namespace openflow{

Define_Module(OF_Controller);



OF_Controller::OF_Controller(){

}

OF_Controller::~OF_Controller(){
    for(auto&& msg : this->msgList) {
      delete msg;
    }
    this->msgList.clear();
}

void OF_Controller::initialize(int stage){
    //register signals
    OperationalBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        PacketInSignalId =registerSignal("PacketIn");
        PacketOutSignalId =registerSignal("PacketOut");
        PacketHelloSignalId =registerSignal("PacketHello");
        PacketFeatureRequestSignalId = registerSignal("PacketFeatureRequest");
        PacketFeatureReplySignalId = registerSignal("PacketFeatureReply");
        PacketExperimenterSignalId = registerSignal("PacketExperimenter");
        BootedSignalId = registerSignal("Booted");

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
    scheduleAt(simTime(), booted);
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


void OF_Controller::handleMessageWhenUp(cMessage *msg){
    if (msg->isSelfMessage()) {
        if (msg->getKind()==MSGKIND_BOOTED){
            this->booted = true;
            emit(BootedSignalId, this);
        }
        else if (msg->getKind() == MSGKIND_EVENT){
            //This is message which has been scheduled due to service time
            //Get the Original message
            cMessage *data_msg = (cMessage *) msg->getContextPointer();
            emit(waitingTime,(simTime()-data_msg->getArrivalTime()-serviceTime));
            auto pktData = check_and_cast<Packet *>(data_msg);
            processQueuedMsg(pktData);

            //delete the processed msg
            delete pktData;

            //Trigger next service time
            if (msgList.empty()){
                busy = false;
            } else {
                cMessage *msgfromlist = msgList.front();
                msgList.pop_front();
                cMessage *event = new cMessage("event");
                event->setKind(MSGKIND_EVENT);
                event->setContextPointer(msgfromlist);
                scheduleAt(simTime()+serviceTime, event);
            }
            calcAvgQueueSize(msgList.size());
        }
        //delete the msg for efficiency
        delete msg;
    }else if (this->booted){
        //imlement service time
        if (!parallelProcessing && busy) {
            msgList.push_back(msg);
        }else{
            busy = true;
            cMessage *event = new cMessage("event");
            event->setContextPointer(msg);
            scheduleAt(simTime()+serviceTime, event);
        }
        else if (msg->getKind() == TCP_I_AVAILABLE) {
            registerConnection(check_and_cast<Indication *>(msg));
            delete msg;
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


void OF_Controller::processQueuedMsg(Packet *pkt){

    const auto chunk = pkt->peekAtFront<Chunk>();
    auto of_msg = dynamicPtrCast<const Open_Flow_Message>(chunk);

    if (of_msg != nullptr) {
        ofp_type type = (ofp_type)of_msg->getHeader().type;
        switch (type) {
            case OFPT_FEATURES_REPLY:
                handleFeaturesReply(pkt);
                break;
            case OFPT_HELLO:
                checkConnection(pkt);
                sendHello(pkt);
                sendFeatureRequest(pkt);
                break;
            case OFPT_PACKET_IN:
                EV << "packet-in message from switch\n";
                handlePacketIn(pkt);
                break;
            case OFPT_VENDOR:
                // the controller apps might want to implement vendor specific features so forward them.
                handleExperimenter(of_msg);
                break;
            default:
                break;
        }
    }
}


void OF_Controller::sendHello(Packet *pkt){
    //Open_Flow_Message *msg
    auto hello = makeShared<OFP_Hello>();
    auto pktHello = new Packet("Hello");
    hello->getHeaderForUpdate().version = OFP_VERSION;
    hello->getHeaderForUpdate().type = OFPT_HELLO;
    hello->setChunkLength(B(8));
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


void OF_Controller::handleExperimenter(Open_Flow_Message* of_msg) {
    EV << "OFA_controller::handleExperimenter" << endl;
    emit(PacketExperimenterSignalId, of_msg);
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


void OF_Controller::checkConnection(Packet *pkt){

    TcpSocket *socket = findSocketFor(pkt);
    auto msg = pkt->peekAtFront<Open_Flow_Message>();
    if(socket == nullptr){
        throw cRuntimeError("Socket not found");

//        socket = new TcpSocket(pkt);
//        socket->setOutputGate(gate("socketOut"));
//        Switch_Info swInfo = Switch_Info();
//        swInfo.setSocket(socket);
//        swInfo.setConnId(socket->getSocketId());
//        swInfo.setMacAddress("");
//        swInfo.setNumOfPorts(-1);
//        swInfo.setVersion(msg->getHeader().version);
//        switchesList.push_back(swInfo);
    }
}


TcpSocket *OF_Controller::findSocketFor(Packet *pkt) const{
    // TcpCommand *ind = dynamic_cast<TcpCommand *>(msg->getControlInfo());
    //if (!ind)
    //    throw cRuntimeError("TcpSocketMap: findSocketFor(): no TCPCommand control info in message (not from TCP?)");
    // int connId = ind->getConnId();
    auto tag = pkt->findTag<SocketInd>();
    if (tag == nullptr)
        throw cRuntimeError("TcpSocketMap: findSocketFor(): no SocketInd (not from TCP?)");
    int connId = pkt->getTag<SocketInd>()->getSocketId();
    for(auto i=switchesList.begin(); i != switchesList.end(); ++i) {
        if((*i).getConnId() == connId){
            return (*i).getSocket();
        }
    }
    return nullptr;
}


Switch_Info *OF_Controller::findSwitchInfoFor(Packet *pkt) {
    auto tag = pkt->findTag<SocketInd>();
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

