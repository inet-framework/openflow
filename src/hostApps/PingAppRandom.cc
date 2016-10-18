



#include "PingAppRandom.h"

#include "IPvXAddressResolver.h"
#include "PingPayload_m.h"
#include "IPv4ControlInfo.h"
#include "IPv6ControlInfo.h"

#include <iostream>
#include <functional>
#include <string>
#include <algorithm>

Define_Module(PingAppRandom);


void PingAppRandom::initialize(int stage){
    if(stage == 0){
        topo.extractByNedTypeName(cStringTokenizer(par("destinationNedType")).asVector());
        EV << "Number of extracted nodes: " << topo.getNumNodes() << endl;
    }
    PingApp::initialize(stage);
    pingPacketHash = registerSignal("pingPacketHash");

}

void PingAppRandom::handleMessage(cMessage *msg){

    if (!isNodeUp()){
            if (msg->isSelfMessage())
                throw cRuntimeError("Application is not running");
            delete msg;
            return;
        }
        if (msg == timer){
            // connect to random destination node
            int random_num = intrand(topo.getNumNodes());
            connectAddress =topo.getNode(random_num)->getModule()->getFullPath().c_str();
            while (topo.getNode(random_num)->getModule() == getParentModule()) {

                // avoid same source and destination
                random_num = intrand(topo.getNumNodes());
                connectAddress =topo.getNode(random_num)->getModule()->getFullPath().c_str();
            }

            destAddr = IPvXAddressResolver().resolve(connectAddress);
            ASSERT(!destAddr.isUnspecified());
            srcAddr = IPvXAddressResolver().resolve(par("srcAddr"));
            EV << "Starting up: dest=" << destAddr << "  src=" << srcAddr << "\n";

            sendPingRequest();
            if (isEnabled())
                scheduleNextPingRequest(simTime());
        }else{
            PingPayload * pingMsg = check_and_cast<PingPayload *>(msg);

            //generate and emit hash
            std::stringstream hashString;
            hashString << "SeqNo-" << pingMsg->getSeqNo() << "-Pid-" << pingMsg->getOriginatorId();
            unsigned long hash = std::hash<std::string>()(hashString.str().c_str());
            emit(pingPacketHash,hash);
            processPingResponse(pingMsg);

        }
        if (ev.isGUI()){
            char buf[40];
            sprintf(buf, "sent: %ld pks\nrcvd: %ld pks", sentCount, numPongs);
            getDisplayString().setTagArg("t", 0, buf);
        }
}


bool PingAppRandom::isEnabled(){
    return (count == -1 || sentCount < count);
}
