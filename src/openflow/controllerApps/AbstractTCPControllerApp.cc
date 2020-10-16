#include "openflow/controllerApps/AbstractTCPControllerApp.h"

namespace openflow{

#define MSGKIND_TCPSERVICETIME                 3098

Define_Module(AbstractTCPControllerApp);

using namespace std;

AbstractTCPControllerApp::AbstractTCPControllerApp()
{

}

AbstractTCPControllerApp::~AbstractTCPControllerApp()
{
    for(auto&& msg : msgList) {
      delete msg;
    }
    msgList.clear();

    for(auto&& pair : socketMap){
        delete pair.second;
    }
    socketMap.clear();
}


void AbstractTCPControllerApp::initialize(){
    AbstractControllerApp::initialize();

    busy = false;
    serviceTime =par("serviceTime");

    queueSize = registerSignal("queueSize");
    waitingTime = registerSignal("waitingTime");

    lastQueueSize =0;
    lastChangeTime=0.0;

}

void AbstractTCPControllerApp::processQueuedMsg(cMessage *msg){

}


void AbstractTCPControllerApp::handleMessage(cMessage *msg){
    if (msg->isSelfMessage()){
        if(msg->getKind()==MSGKIND_TCPSERVICETIME){
            //This is message which has been scheduled due to service time

            //Get the Original message
            cMessage *data_msg = (cMessage *) msg->getContextPointer();
            emit(waitingTime,(simTime()-data_msg->getArrivalTime()-serviceTime));
            processQueuedMsg(data_msg);


            //Trigger next service time
            if (msgList.empty()){
                busy = false;
            } else {
                cMessage *msgFromList = msgList.front();
                msgList.pop_front();
                cMessage *event = new cMessage("event");
                event->setKind(MSGKIND_TCPSERVICETIME);
                event->setContextPointer(msgFromList);
                scheduleAt(simTime()+serviceTime, event);
            }
            calcAvgQueueSize(msgList.size());

            //delete the msg for efficiency
            delete msg;
        }


    } else {
            //imlement service time
            if (busy) {
                msgList.push_back(msg);
            } else {
                busy = true;
                cMessage *event = new cMessage("event");
                event->setKind(MSGKIND_TCPSERVICETIME);
                event->setContextPointer(msg);
                scheduleAt(simTime()+serviceTime, event);
            }
            emit(queueSize,static_cast<unsigned long>(msgList.size()));
            if(packetsPerSecond.count(floor(simTime().dbl())) <=0){
                packetsPerSecond.insert(pair<int,int>(floor(simTime().dbl()),1));
            } else {
                packetsPerSecond[floor(simTime().dbl())]++;
            }
            calcAvgQueueSize(msgList.size());
    }
}

TCPSocket * AbstractTCPControllerApp::findSocketFor(cMessage *msg) {
    TCPCommand *ind = dynamic_cast<TCPCommand *>(msg->getControlInfo());
    if (!ind)
        throw cRuntimeError("SocketMap: findSocketFor(): no TCPCommand control info in message (not from TCP?)");

    std::map<int,TCPSocket*>::iterator i = socketMap.find(ind->getConnId());
    ASSERT(i==socketMap.end() || i->first==i->second->getConnectionId());
    return (i==socketMap.end()) ? NULL : i->second;
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
}

} /*end namespace openflow*/


