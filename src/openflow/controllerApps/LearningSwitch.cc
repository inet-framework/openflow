#include "openflow/controllerApps/LearningSwitch.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/openflow/protocol/OFMatchFactory.h"

namespace openflow{

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

void LearningSwitch::receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) {
    AbstractControllerApp::receiveSignal(src,id,obj,details);

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

            auto builder = OFMatchFactory::getBuilder();
            builder->setField(OFPXMT_OFB_ETH_DST, &headerFields.dst_mac);
            builder->setField(OFPXMT_OFB_ETH_TYPE, &headerFields.eth_type);
            builder->setField(OFPXMT_OFB_ETH_SRC, &headerFields.src_mac);
            builder->setField(OFPXMT_OFB_IN_PORT, &headerFields.inport);
            oxm_basic_match match = builder->build();

            TCPSocket * socket = controller->findSocketFor(packet_in_msg);
            sendFlowModMessage(OFPFC_ADD, match, outport, socket,idleTimeout,hardTimeout);
            sendPacket(packet_in_msg, outport);
        }
    }
}

} /*end namespace openflow*/

