#include "openflow/controllerApps/AbstractTCPControllerApp.h"
#include "inet/common/socket/SocketTag_m.h"
#include "inet/transportlayer/contract/tcp/TcpCommand_m.h"

namespace openflow{

// Define_Module(AbstractTCPControllerApp);

using namespace std;

AbstractTCPControllerApp::AbstractTCPControllerApp()
{

}

AbstractTCPControllerApp::~AbstractTCPControllerApp()
{
    for(auto&& msg : msgList) {
      delete msg.msg;
    }
    msgList.clear();
}


void AbstractTCPControllerApp::initialize(int stage){
    AbstractControllerApp::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        busy = false;
        serviceTime =par("serviceTime");
        queueSize = registerSignal("queueSize");
        waitingTime = registerSignal("waitingTime");
        lastQueueSize =0;
        lastChangeTime=0.0;
    }
}

void AbstractTCPControllerApp::startProcessingMsg(Action& action)
{
    busy = true;
    cMessage *msg = action.msg;
    cMessage *event = new cMessage("event");
    event->setKind(action.kind);
    event->setContextPointer(msg);
    EV_DEBUG << "Start processing of message " << msg->getName() << endl;
    scheduleAt(simTime()+serviceTime, event);
}

void AbstractTCPControllerApp::processSelfMessage(cMessage *msg) {
    if(msg->getKind() == ACTION_EVENT || msg->getKind() == ACTION_DATA) {
        //This is message which has been scheduled due to service time
        //Get the Original message
        cMessage *data_msg = (cMessage *) msg->getContextPointer();
        EV_DEBUG << "End of processing message " << data_msg->getName() << endl;
        emit(waitingTime,(simTime()-data_msg->getArrivalTime()-serviceTime));

        if (msg->getKind() == ACTION_EVENT)
            processQueuedMsg(data_msg);
        else if (msg->getKind() == ACTION_DATA)
            processPacketFromTcp(check_and_cast<Packet *>(data_msg));
        else
            throw cRuntimeError("model error");

        //Trigger next service time
        if (msgList.empty()){
            busy = false;
        } else {
            auto msgFromList = msgList.front();
            msgList.pop_front();
            startProcessingMsg(msgFromList);
        }
        calcAvgQueueSize(msgList.size());
        //delete the msg for efficiency
        delete msg;
    }
}

void AbstractTCPControllerApp::handleMessageWhenUp(cMessage *msg){
    if (msg->isSelfMessage()){
        processSelfMessage(msg);
    } else {
        if (msg->isPacket()) {
            if(packetsPerSecond.count(floor(simTime().dbl())) <=0){
                packetsPerSecond.insert(pair<int,int>(floor(simTime().dbl()),1));
            } else {
                packetsPerSecond[floor(simTime().dbl())]++;
            }
        }
        //imlement service time
        if (msg->getKind() == TCP_I_DATA || msg->getKind() == TCP_I_URGENT_DATA || msg->getKind() == TCP_I_AVAILABLE)
            processQueuedMsg(msg);
        else {
            Action action(ACTION_EVENT, msg);
            if (busy) {
                msgList.push_back(action);
            } else {
                startProcessingMsg(action);
            }
        }
        calcAvgQueueSize(msgList.size());
        emit(queueSize,msgList.size());
    }
}

void AbstractTCPControllerApp::calcAvgQueueSize(int size){
    if(lastQueueSize != size){
        double timeDiff = simTime().dbl() - lastChangeTime;
        if(avgQueueSize.count(floor(simTime().dbl())) <=0){
            avgQueueSize.insert(pair<int,double>(floor(simTime().dbl()),lastQueueSize*timeDiff));
        } else {
            avgQueueSize[floor(simTime().dbl())] += lastQueueSize*timeDiff;
        }
            lastChangeTime = simTime().dbl();
            lastQueueSize = size;
        }
}

void AbstractTCPControllerApp::finish(){
    // record statistics

    //std::map<int,int>::iterator iterMap;
    /*
    for(auto iterMap = packetsPerSecond.begin(); iterMap != packetsPerSecond.end(); ++iterMap){
        stringstream name;
        name << "packetsPerSecondAt-" << iterMap->first;
        recordScalar(name.str().c_str(),iterMap->second);
    }

    //std::map<int,double>::iterator iterMap2;
    for(auto iterMap2 = avgQueueSize.begin(); iterMap2 != avgQueueSize.end(); ++iterMap2){
        stringstream name;
        name << "avgQueueSizeAt-" << iterMap2->first;
        recordScalar(name.str().c_str(),(iterMap2->second/1.0));
    }
    */
    for(auto elem : packetsPerSecond){
        stringstream name;
        name << "packetsPerSecondAt-" << elem.first;
        recordScalar(name.str().c_str(),elem.second);
    }

    for(auto elem :avgQueueSize){
        stringstream name;
        name << "avgQueueSizeAt-" << elem.first;
        recordScalar(name.str().c_str(),(elem.second/1.0));
    }
}

void AbstractTCPControllerApp::socketEstablished(TcpSocket *socket)
{
}

void AbstractTCPControllerApp::socketAvailable(TcpSocket *listenerSocket, TcpAvailableInfo *availableInfo)
{
    throw cRuntimeError("TCP AVAILABLE is unsupported in this module");
}

void AbstractTCPControllerApp::socketPeerClosed(TcpSocket *socket)
{
}

void AbstractTCPControllerApp::socketClosed(TcpSocket *socket)
{
}

void AbstractTCPControllerApp::socketFailure(TcpSocket *socket, int code)
{
}

} /*end namespace openflow*/


