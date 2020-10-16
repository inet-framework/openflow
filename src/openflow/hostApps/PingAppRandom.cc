



#include "openflow/hostApps/PingAppRandom.h"

#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/applications/pingapp/PingPayload_m.h"
#include "inet/networklayer/contract/ipv4/IPv4ControlInfo.h"
#include "inet/networklayer/contract/ipv6/IPv6ControlInfo.h"

#include <iostream>
#include <functional>
#include <string>
#include <algorithm>

using namespace inet;

namespace openflow{

Define_Module(PingAppRandom);


void PingAppRandom::initialize(int stage){
    if (stage == INITSTAGE_LOCAL){
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
            unsigned nodeNum = topo.getNumNodes();
            if (nodeNum == 0)
                throw cRuntimeError("No potential destination nodes found");
            int random_num = intrand(nodeNum);
            connectAddress =topo.getNode(random_num)->getModule()->getFullPath();
            while (topo.getNode(random_num)->getModule() == getParentModule()) {

                // avoid same source and destination
                random_num = intrand(topo.getNumNodes());
                connectAddress =topo.getNode(random_num)->getModule()->getFullPath();
            }

            destAddr = inet::L3AddressResolver().resolve(connectAddress.c_str());
            ASSERT(!destAddr.isUnspecified());
            srcAddr = inet::L3AddressResolver().resolve(par("srcAddr"));
            EV << "Starting up: dest=" << destAddr << "  src=" << srcAddr << "\n";

            sendPing();
            if (isEnabled())
                scheduleNextPingRequest(simTime(), true);
        } else {
            inet::PingPayload * pingMsg = check_and_cast<inet::PingPayload *>(msg);

            //generate and emit hash
            std::stringstream hashString;
            hashString << "SeqNo-" << pingMsg->getSeqNo() << "-Pid-" << pingMsg->getOriginatorId();
            unsigned long hash = std::hash<std::string>()(hashString.str().c_str());
            emit(pingPacketHash,hash);
            processPingResponse(pingMsg);

        }
        if (hasGUI()){
            char buf[40];
            sprintf(buf, "sent: %ld pks\nrcvd: %ld pks", sentCount, numPongs);
            getDisplayString().setTagArg("t", 0, buf);
        }
}


bool PingAppRandom::isEnabled(){
    return (count == -1 || sentCount < count);
}

} /*end namespace openflow*/
