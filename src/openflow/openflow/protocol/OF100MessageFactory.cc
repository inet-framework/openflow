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

#include "openflow/openflow/protocol/OF100MessageFactory.h"
#include <openflow/openflow/protocol/OpenFlow.h>
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

    //set openflow header 8 Byte
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_FEATURES_REPLY;

    //set data fields
    msg->setDatapath_id(dpid.c_str()); // 8 Byte
    msg->setN_buffers(n_buffers); // 4 Byte
    msg->setN_tables(n_tables); // 4 Byte (= 1 Byte + 3 Byte Padding)
    msg->setCapabilities(capabilities); // 4 Byte + actions 4 Byte = 8 Byte
    msg->setPortsArraySize(n_ports); // 10 Byte per port --> n_ports * 10
    //set message size
    msg->setByteLength(24 + n_ports*10);

    return msg;
}

OFP_Features_Request* OF100MessageFactory::createFeatureRequest() {

    OFP_Features_Request *featuresRequest = new OFP_Features_Request("FeaturesRequest");

    //set header info 8 Byte
    featuresRequest->getHeader().version = OFP_VERSION;
    featuresRequest->getHeader().type = OFPT_FEATURES_REQUEST;


    //set message params
    featuresRequest->setByteLength(8);

    return featuresRequest;
}

OFP_Flow_Mod* OF100MessageFactory::createFlowModMessage(ofp_flow_mod_command mod_com,const oxm_basic_match& match, int pritority, uint32_t* outports, int n_outports, uint32_t idleTimeOut, uint32_t hardTimeOut) {
    OFP_Flow_Mod *msg = new OFP_Flow_Mod("flow_mod");

    //set header info 8 Byte
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_FLOW_MOD;

    //set data fields
    msg->setMatch(match); //40 Byte
    msg->setCommand(mod_com); // 2 Byte
    msg->setHard_timeout(hardTimeOut); // 1 Byte
    msg->setIdle_timeout(idleTimeOut); // 1 Byte
    msg->setPriority(pritority);       // 1 Byte
    // 4 Byte buffer_id

    msg->setFlags(0); // 2 Byte
    msg->setCookie(42); // 8 Byte
    msg->setOut_port(outports[0]); // 2 Byte

    msg->setActionsArraySize(n_outports); // 4 Byte per output action.
    for(int i=0; i<n_outports; i++) {
        ofp_action_output* action_output = new ofp_action_output();
        action_output->port = outports[i];
        msg->setActions(i, *action_output);
    }

    //set message params
    msg->setByteLength(69+4*n_outports);

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
   OFP_Packet_In *msg = new OFP_Packet_In("packetIn");

   //create header 8 Byte
   msg->getHeader().version = OFP_VERSION;
   msg->getHeader().type = OFPT_PACKET_IN;

   //set data fields
   msg->setBuffer_id(buffer_id); // 4 Byte
   // total_len 2 Byte
   // in_port 2 Byte
   msg->setReason(reason); // 1 Byte
   // pad 1 Byte

   if(sendFullFrame){
       msg->setByteLength(18);
       msg->encapsulate(frame->dup());
   } else {
       // packet in buffer so only send header fields
       oxm_basic_match match = oxm_basic_match();
       match.OFB_IN_PORT = frame->getArrivalGate()->getIndex();

       match.OFB_ETH_SRC = frame->getSrc();
       match.OFB_ETH_DST = frame->getDest();
       match.OFB_ETH_TYPE = frame->getEtherType();
       //extract ARP specific match fields if present
       if(frame->getEtherType()==ETHERTYPE_ARP){
           ARPPacket *arpPacket = check_and_cast<ARPPacket *>(frame->getEncapsulatedPacket());
           match.OFB_IP_PROTO = arpPacket->getOpcode();
           match.OFB_IPV4_SRC = arpPacket->getSrcIPAddress();
           match.OFB_IPV4_DST = arpPacket->getDestIPAddress();
       }
       msg->setMatch(match);// 6 Byte
       msg->setByteLength(24);
   }

    return msg;
}

OFP_Packet_Out* OF100MessageFactory::createPacketOut(uint32_t* outports, int n_outports, int in_port, uint32_t buffer_id, EthernetIIFrame *frame) {
    OFP_Packet_Out *msg = new OFP_Packet_Out("packetOut");

    //create header 8 Byte
    msg->getHeader().version = OFP_VERSION;
    msg->getHeader().type = OFPT_PACKET_OUT;

    msg->setBuffer_id(buffer_id); // 4 Byte
    msg->setIn_port(in_port); // 2 Byte
    // actions_len 2 Byte

    msg->setActionsArraySize(n_outports); // 4 Byte per output action.
    for(int i=0; i<n_outports; i++) {
        ofp_action_output* action_output = new ofp_action_output();
        action_output->port = outports[i];
        msg->setActions(i, *action_output);
    }

    msg->setByteLength(16 + 4*n_outports);

    if (buffer_id == OFP_NO_BUFFER)
    {   //No Buffer so send full frame.
        if(frame){
            msg->encapsulate(frame->dup());
        } else {
            throw cRuntimeError("OF100MessageFactory::createPacketOut: OFP_NO_BUFFER was set but no frame was provided.");
        }
    }

    return msg;
}

} /* namespace openflow */
