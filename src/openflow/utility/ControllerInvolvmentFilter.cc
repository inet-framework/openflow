#include "ControllerInvolvementFilter.h"



Define_Module(ControllerInvolvementFilter);


void ControllerInvolvementFilter::initialize(int stage) {
    cpPingPacketHash = registerSignal("cpPingPacketHash");
    getParentModule()->subscribe("cpPingPacketHash",this);
}

void ControllerInvolvementFilter::receiveSignal(cComponent *source, simsignal_t signalID, unsigned long l){
    if(signalID==cpPingPacketHash){
        if(controllerInvolvements.count(l) <=0){
            controllerInvolvements.insert(std::pair<long,int>(l,1));
        } else {
            controllerInvolvements[l]++;
        }
    }
}

void ControllerInvolvementFilter::handleMessage(cMessage *msg) {
    error("this module doesn't handle messages, it runs only in initialize()");
}

void ControllerInvolvementFilter::finish(){
    std::map<long,int>::iterator iterMap;
    for(iterMap = controllerInvolvements.begin(); iterMap != controllerInvolvements.end(); iterMap++){
        std::stringstream name;
        name << "controllerInvolvementsFor-" << iterMap->first;
        recordScalar(name.str().c_str(),iterMap->second);
    }
}
