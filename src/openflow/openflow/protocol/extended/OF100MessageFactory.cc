//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// c Timo Haeckel, for HAW Hamburg
//

#include "openflow/openflow/protocol/extended/OF100MessageFactory.h"
#include <openflow/openflow/protocol/extended/OpenFlow.h>
#include <openflow/messages/OFP_Features_Reply_m.h>
#include <openflow/messages/OFP_Features_Request_m.h>
#include <openflow/messages/OFP_Flow_Mod_m.h>
#include <openflow/messages/OFP_Hello_m.h>
#include <openflow/messages/OFP_Packet_In_m.h>
#include <openflow/messages/OFP_Packet_Out_m.h>

#include "inet/networklayer/arp/ipv4/ARPPacket_m.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"

using namespace inet;

namespace openflow {

OF100MessageFactory::OF100MessageFactory() {

}

OF100MessageFactory::~OF100MessageFactory() {
}

OFP_Features_Reply* OF100MessageFactory::createFeaturesReply(std::string dpid,
        uint32_t n_buffers, uint8_t n_tables, uint32_t capabilities, uint32_t n_ports) {
    OFP_Features_Reply* msg = new OFP_Features_Reply("FeaturesReply");

    //set openflow header
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_FEATURES_REPLY;

    //set data fields
    msg->setDatapath_id(dpid.c_str());
    msg->setN_buffers(n_buffers);
    msg->setN_tables(n_tables);
    msg->setCapabilities(capabilities);
    msg->setPortsArraySize(n_ports);

    //set message params
    msg->setByteLength(32);

    return msg;
}

OFP_Features_Request* OF100MessageFactory::createFeatureRequest() {

    OFP_Features_Request *featuresRequest = new OFP_Features_Request("FeaturesRequest");

    //set header info
    featuresRequest->getHeader().version = OFP_VERSION;
    featuresRequest->getHeader().type = OFPT_FEATURES_REQUEST;


    //set message params
    featuresRequest->setByteLength(8);

    return featuresRequest;
}

OFP_Flow_Mod* OF100MessageFactory::createFlowModMessage(ofp_flow_mod_command mod_com,const oxm_basic_match& match, int pritority, uint32_t* outports, int n_outports, uint32_t idleTimeOut, uint32_t hardTimeOut) {
    OFP_Flow_Mod *msg = new OFP_Flow_Mod("flow_mod");

    //set header info
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_FLOW_MOD;

    //set data fields
    msg->setCommand(mod_com);
    //TODO create OFP Match for version 1.0 - 1.3
    //msg->setMatch(match->toOXMBasicMatch);
    msg->setMatch(match);
    msg->setHard_timeout(hardTimeOut);
    msg->setIdle_timeout(idleTimeOut);

    msg->setFlags(0);
    msg->setCookie(42);

    msg->setActionsArraySize(n_outports);
    for(int i=0; i<n_outports; i++) {
        ofp_action_output* action_output = new ofp_action_output();
        action_output->port = outports[i];
        msg->setActions(i, *action_output);
    }

    //set message params
    msg->setByteLength(56);

    return msg;
}

OFP_Hello* OF100MessageFactory::createHello() {
    OFP_Hello *msg = new OFP_Hello("Hello");
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_HELLO;
    msg->setByteLength(8);
    return msg;
}

OFP_Packet_In* OF100MessageFactory::createPacketIn(ofp_packet_in_reason reason, EthernetIIFrame *frame, uint32_t buffer_id, bool sendFullFrame) {

   //TODO maybe use custom reason to abstract from differing openflow versions

   OFP_Packet_In *msg = new OFP_Packet_In("packetIn");

   //create header
   msg->getHeader().version = OFP_VERSION;
   msg->getHeader().type = OFPT_PACKET_IN;

   //set data fields
   msg->setReason(reason);
   if(sendFullFrame){
       msg->encapsulate(frame->dup());
       msg->setBuffer_id(buffer_id);
   } else {
       // packet in buffer so only send header fields
       oxm_basic_match match = oxm_basic_match();
       match.in_port = frame->getArrivalGate()->getIndex();

       match.dl_src = frame->getSrc();
       match.dl_dst = frame->getDest();
       match.dl_type = frame->getEtherType();
       //extract ARP specific match fields if present
       if(frame->getEtherType()==ETHERTYPE_ARP){
           ARPPacket *arpPacket = check_and_cast<ARPPacket *>(frame->getEncapsulatedPacket());
           match.nw_proto = arpPacket->getOpcode();
           match.nw_src = arpPacket->getSrcIPAddress();
           match.nw_dst = arpPacket->getDestIPAddress();
       }
       msg->setMatch(match);
       msg->setBuffer_id(buffer_id);
   }


   msg->setByteLength(32);

    return msg;
}

OFP_Packet_Out* OF100MessageFactory::createPacketOut(uint32_t* outports, int n_outports, int in_port, uint32_t buffer_id, EthernetIIFrame *frame) {
    OFP_Packet_Out *msg = new OFP_Packet_Out("packetOut");

    //create header
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_PACKET_OUT;
    msg->setBuffer_id(buffer_id);

    if (buffer_id == OFP_NO_BUFFER)
    {   //No Buffer so send full frame.
        if(frame){
            msg->encapsulate(frame->dup());
            msg->setIn_port(in_port);
        } else {
            throw cRuntimeError("OF100MessageFactory::createPacketOut: OFP_NO_BUFFER was set but no frame was provided.");
        }
    } else {
        msg->setIn_port(in_port);
    }

    msg->setActionsArraySize(n_outports);
    for(int i=0; i<n_outports; i++) {
        ofp_action_output* action_output = new ofp_action_output();
        action_output->port = outports[i];
        msg->setActions(i, *action_output);
    }


    msg->setByteLength(24);

    return msg;
}

} /* namespace openflow */
