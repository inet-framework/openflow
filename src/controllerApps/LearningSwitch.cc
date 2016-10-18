#include <LearningSwitch.h>
#include "Switch_Info.h"

Define_Module(LearningSwitch);

LearningSwitch::LearningSwitch(){

}

LearningSwitch::~LearningSwitch(){

}

void LearningSwitch::initialize(){
    AbstractControllerApp::initialize();
    idleTimeout = par("flowModIdleTimeOut");
    hardTimeout = par("flowModHardTimeOut");
}

void LearningSwitch::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    AbstractControllerApp::receiveSignal(src,id,obj);

    if(id == PacketInSignalId){
        EV << "LearningSwitch::PacketIn" << endl;
        if (dynamic_cast<OFP_Packet_In *>(obj) != NULL) {
            OFP_Packet_In *packet_in = (OFP_Packet_In *) obj;
            doSwitching(packet_in);
        }
    }
}


void LearningSwitch::doSwitching(OFP_Packet_In *packet_in_msg){

    CommonHeaderFields headerFields = extractCommonHeaderFields(packet_in_msg);

    //search map for source mac address and enter
    if(lookupTable.count(headerFields.swInfo)<=0){
        lookupTable[headerFields.swInfo]= std::map<MACAddress,uint32_t>();
        lookupTable[headerFields.swInfo][headerFields.src_mac] = headerFields.inport;
    } else {
        if(lookupTable[headerFields.swInfo].count(headerFields.src_mac)<=0){
            lookupTable[headerFields.swInfo][headerFields.src_mac] = headerFields.inport;
        }
    }


    if(lookupTable.count(headerFields.swInfo)<=0){
        floodPacket(packet_in_msg);
    } else {
        if(lookupTable[headerFields.swInfo].count(headerFields.dst_mac)<=0){
            floodPacket(packet_in_msg);
        } else {
            uint32_t outport = lookupTable[headerFields.swInfo][headerFields.dst_mac];

            oxm_basic_match match = oxm_basic_match();
            match.OFB_ETH_DST = headerFields.dst_mac;
            match.OFB_ETH_TYPE = headerFields.eth_type;
            match.OFB_ETH_SRC = headerFields.src_mac;
            match.OFB_IN_PORT = headerFields.inport;

            match.wildcards= 0;
            match.wildcards |= OFPFW_IN_PORT;
            match.wildcards |=  OFPFW_DL_SRC;
            match.wildcards |= OFPFW_DL_TYPE;



            TCPSocket * socket = controller->findSocketFor(packet_in_msg);
            sendFlowModMessage(OFPFC_ADD, match, outport, socket,idleTimeout,hardTimeout);
            sendPacket(packet_in_msg, outport);
        }
    }
}







