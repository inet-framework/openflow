

#include <iostream>

#include "openflow/hostApps/LocalityPingAppRandom.h"

#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/applications/pingapp/PingPayload_m.h"
#include "inet/networklayer/contract/ipv4/IPv4ControlInfo.h"
#include "inet/networklayer/contract/ipv6/IPv6ControlInfo.h"

using namespace std;
using std::cout;

namespace openflow{

Define_Module(LocalityPingAppRandom);


void LocalityPingAppRandom::initialize(int stage){
    if(stage == INITSTAGE_LOCAL){
        //set params
        localityRelation = par("localityRelation");

        //read in config
        std::string path = par("pathToGroupConfigFile");
        ifstream ifs( path.c_str() );
        if(ifs){
            string node="";
            string group="";
            string line="";
            while(!ifs.eof()){
                getline(ifs, line);

                node = (cStringTokenizer(line.c_str(),";").asVector())[0];
                group = (cStringTokenizer(line.c_str(),";").asVector())[1];

                //check if the node is me
                if(strstr(getParentModule()->getFullPath().c_str(),node.c_str())!=NULL){
                    localId = group;
                } else {
                    if(groupToNodes.count(group)== 0){
                        groupToNodes[group] = std::vector<std::string>();
                        groupToNodes[group].push_back(node);
                    } else {
                        groupToNodes[group].push_back(node);
                    }
                }
            }
        } else {
            EV << "File not found!" << endl;
        }
        ifs.close();

    }
    PingApp::initialize(stage);
}

void LocalityPingAppRandom::handleMessage(cMessage *msg){

    if (!isNodeUp()){
            if (msg->isSelfMessage())
                throw cRuntimeError("Application is not running");
            delete msg;
            return;
        }
        if (msg == timer){
            //determine local oder global
            if(dblrand() <= localityRelation){
                //determine random local target
                std::vector<std::string> tempVec = groupToNodes[localId];
                connectAddress = (tempVec[intrand(groupToNodes[localId].size())]);

            } else {
                //determine random global target

                //determine group
                int tempRand = intrand(groupToNodes.size());
                while(tempRand == atoi(localId.c_str())){
                    tempRand = intrand(groupToNodes.size());
                }
                //determine host
                std::vector<std::string> tempVec = groupToNodes[std::to_string(tempRand)];
                connectAddress = (tempVec[intrand(groupToNodes[std::to_string(tempRand)].size())]);
            }


            destAddr = L3AddressResolver().resolve(connectAddress.c_str());
            ASSERT(!destAddr.isUnspecified());
            srcAddr = L3AddressResolver().resolve(par("srcAddr"));
            EV << "Starting up: dest=" << destAddr << "  src=" << srcAddr << "\n";

            sendPing();
            if (isEnabled())
                scheduleNextPingRequest(simTime(), true);
        }
        else
            processPingResponse(check_and_cast<PingPayload *>(msg));

        if (hasGUI()){
            char buf[40];
            sprintf(buf, "sent: %ld pks\nrcvd: %ld pks", sentCount, numPongs);
            getDisplayString().setTagArg("t", 0, buf);
        }
}


bool LocalityPingAppRandom::isEnabled(){
    return (count == -1 || sentCount < count);
}

} /*end namespace openflow*/
