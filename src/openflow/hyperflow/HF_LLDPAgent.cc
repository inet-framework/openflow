#include "openflow/hyperflow/HF_LLDPAgent.h"
#include <algorithm>

#define MSGKIND_TRIGGERLLDP 101
#define MSGKIND_LLDPAGENTBOOTED 201

namespace openflow{

Define_Module(HF_LLDPAgent);

HF_LLDPAgent::HF_LLDPAgent(){

}

HF_LLDPAgent::~HF_LLDPAgent(){

}

void HF_LLDPAgent::initialize(){
    LLDPAgent::initialize();
    hfAgent = NULL;

    //register signals
    HyperFlowReFireSignalId =registerSignal("HyperFlowReFire");
    getParentModule()->subscribe("HyperFlowReFire",this);

}






void HF_LLDPAgent::handlePacketIn(OFP_Packet_In * packet_in_msg){

    CommonHeaderFields headerFields = extractCommonHeaderFields(packet_in_msg);

    //check if it is an lldp packet
    if(headerFields.eth_type == 0x88CC){
        EthernetIIFrame *frame =  dynamic_cast<EthernetIIFrame *>(packet_in_msg->getEncapsulatedPacket());
        //check if we have received the entire frame, if not the flow mods have not been sent yet
        if(frame != NULL){
            LLDP *lldp = (LLDP *) frame->getEncapsulatedPacket();
            mibGraph.addEntry(lldp->getChassisID(),lldp->getPortID(),headerFields.swInfo->getMacAddress(),headerFields.inport,timeOut);
            if(printMibGraph){
                EV << mibGraph.getStringGraph() << endl;
            }

            //inform hyperflow
            LLDP_Wrapper *wrapper = new LLDP_Wrapper();
            wrapper->setDstId(headerFields.swInfo->getMacAddress());
            wrapper->setDstPort(headerFields.inport);
            wrapper->setSrcId(lldp->getChassisID());
            wrapper->setSrcPort(lldp->getPortID());

            DataChannelEntry entry = DataChannelEntry();
            entry.eventId = 0;
            entry.trgSwitch = "";
            entry.srcController = controller->getFullPath();
            entry.payload = wrapper;

            hfAgent->synchronizeDataChannelEntry(entry);

        } else {
            //resend flow mod
            triggerFlowMod(headerFields.swInfo);
        }

     } else {
         //this could be a packet originating from an end device, check if the port is associated with an lldp entry
         if(mibGraph.addEntry(headerFields.src_mac.str(),-1,headerFields.swInfo->getMacAddress(),headerFields.inport,timeOut)){
             if(printMibGraph){
                 EV << mibGraph.getStringGraph() << endl;
             }

             //inform hyperflow
             LLDP_Wrapper *wrapper = new LLDP_Wrapper();
             wrapper->setDstId(headerFields.swInfo->getMacAddress());
             wrapper->setDstPort(headerFields.inport);
             wrapper->setSrcId(headerFields.src_mac.str());
             wrapper->setSrcPort(-1);

             DataChannelEntry entry = DataChannelEntry();
             entry.eventId = 0;
             entry.trgSwitch = "";
             entry.srcController = controller->getFullPath();
             entry.payload = wrapper;

             hfAgent->synchronizeDataChannelEntry(entry);
         }
     }



}


void HF_LLDPAgent::receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) {
    //set hfagent link
    if(hfAgent == NULL && controller != NULL){
        auto appList = controller->getAppList();

        for(auto iterApp=appList->begin();iterApp!=appList->end();++iterApp){
            if(dynamic_cast<HyperFlowAgent *>(*iterApp) != NULL) {
                HyperFlowAgent *hf = (HyperFlowAgent *) *iterApp;
                hfAgent = hf;
                break;
            }
        }
    }

    LLDPAgent::receiveSignal(src,id,obj,details);

    //check for hf messages to refire
    if(id == HyperFlowReFireSignalId){
        if(dynamic_cast<HF_ReFire_Wrapper *>(obj) != NULL) {
            HF_ReFire_Wrapper *hfRefire = (HF_ReFire_Wrapper *) obj;
            if(strcmp(hfRefire->getDataChannelEntry().trgSwitch.c_str(),"") == 0){
                if (dynamic_cast<LLDP_Wrapper *>(hfRefire->getDataChannelEntry().payload) != NULL) {
                    LLDP_Wrapper *wrapper = (LLDP_Wrapper *) hfRefire->getDataChannelEntry().payload;
                    mibGraph.addEntry(wrapper->getSrcId(),wrapper->getSrcPort(),wrapper->getDstId(),wrapper->getDstPort(),timeOut);
                    if(printMibGraph){
                        EV << mibGraph.getStringGraph() << endl;
                    }
                }
            }
        }
    }

}

} /*end namespace openflow*/


