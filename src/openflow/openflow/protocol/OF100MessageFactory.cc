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

#include "inet/networklayer/arp/ipv4/ArpPacket_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/ethernet/common/EthernetMacHeader_m.h"

using namespace inet;

namespace openflow {

OF100MessageFactory::OF100MessageFactory() {

}

OF100MessageFactory::~OF100MessageFactory() {
}

Packet* OF100MessageFactory::createFeaturesReply(std::string dpid,
        uint32_t n_buffers, uint8_t n_tables, uint32_t capabilities, uint32_t n_ports) {
    auto msg = makeShared<OFP_Features_Reply>();
    auto pk = new Packet("FeaturesReply");

    //set openflow header 8 Byte
    msg->getHeaderForUpdate().version = OFP_VERSION;
    msg->getHeaderForUpdate().type = OFPT_FEATURES_REPLY;

    //set data fields
    msg->setDatapath_id(dpid.c_str()); // 8 Byte
    msg->setN_buffers(n_buffers); // 4 Byte
    msg->setN_tables(n_tables); // 4 Byte (= 1 Byte + 3 Byte Padding)
    msg->setCapabilities(capabilities); // 4 Byte + actions 4 Byte = 8 Byte
    msg->setPortsArraySize(n_ports); // 10 Byte per port --> n_ports * 10
    //set message size
    msg->setChunkLength(B(24 + n_ports*10));
    msg->getHeaderForUpdate().length = B(msg->getChunkLength()).get() + pk->getByteLength();

    pk->insertAtFront(msg);
    return pk;
}

Packet* OF100MessageFactory::createFeatureRequest() {

    auto featuresRequest = makeShared<OFP_Features_Request>();
    auto pk = new Packet("FeaturesRequest");

    //set header info 8 Byte
    featuresRequest->getHeaderForUpdate().version = OFP_VERSION;
    featuresRequest->getHeaderForUpdate().type = OFPT_FEATURES_REQUEST;


    //set message params
    featuresRequest->setChunkLength(B(8));
    featuresRequest->getHeaderForUpdate().length = 8;

    pk->insertAtFront(featuresRequest);
    return pk;
}

Packet* OF100MessageFactory::createFlowModMessage(ofp_flow_mod_command mod_com,const oxm_basic_match& match, int pritority, uint32_t* outports, int n_outports, uint32_t idleTimeOut, uint32_t hardTimeOut) {
    auto msg = makeShared<OFP_Flow_Mod>();
    auto pk = new Packet("flow_mod");

    //set header info 8 Byte
    msg->getHeaderForUpdate().version = OFP_VERSION;
    msg->getHeaderForUpdate().type = OFPT_FLOW_MOD;

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
    msg->setChunkLength(B(69+4*n_outports));
    msg->getHeaderForUpdate().length = B(msg->getChunkLength()).get() + pk->getByteLength();

    pk->insertAtFront(msg);
    return pk;
}

Packet* OF100MessageFactory::createHello() {
    auto msg = makeShared<OFP_Hello>();
    auto pk = new Packet("Hello");
    msg->getHeaderForUpdate().version = OFP_VERSION;
    msg->getHeaderForUpdate().type = OFPT_HELLO;
    msg->setChunkLength(B(8));
    msg->getHeaderForUpdate().length = 8;
    pk->insertAtFront(msg);
    return pk;
}

Packet* OF100MessageFactory::createPacketIn(ofp_packet_in_reason reason, Packet *ethPk, uint32_t buffer_id, bool sendFullFrame) {
   auto msg = makeShared<OFP_Packet_In>();
   auto pk = new Packet("packetIn");

   //create header 8 Byte
   msg->getHeaderForUpdate().version = OFP_VERSION;
   msg->getHeaderForUpdate().type = OFPT_PACKET_IN;

   //set data fields
   msg->setBuffer_id(buffer_id); // 4 Byte
   // total_len 2 Byte
   // in_port 2 Byte
   msg->setReason(reason); // 1 Byte
   // pad 1 Byte

   if(sendFullFrame){
       msg->setChunkLength(B(18));
       // msg->encapsulate(frame->dup());
       pk->insertAtFront(ethPk->peekData());
       msg->getHeaderForUpdate().length = 18 + pk->getByteLength();
       oxm_basic_match match = oxm_basic_match();
       match.OFB_IN_PORT = ethPk->getTag<InterfaceInd>()->getInterfaceId();
//       match.OFB_ETH_SRC = frame->getSrc();
//       match.OFB_ETH_DST = frame->getDest();
//       match.OFB_ETH_TYPE = frame->getTypeOrLength();
       msg->setMatch(match);
       pk->insertAtFront(msg);
   } else {
       auto frame = ethPk->popAtFront<EthernetMacHeader>();
       // packet in buffer so only send header fields
       oxm_basic_match match = oxm_basic_match();
       match.OFB_IN_PORT = ethPk->getTag<InterfaceInd>()->getInterfaceId();

       match.OFB_ETH_SRC = frame->getSrc();
       match.OFB_ETH_DST = frame->getDest();
       match.OFB_ETH_TYPE = frame->getTypeOrLength();
       //extract ARP specific match fields if present
       if (frame->getTypeOrLength() == ETHERTYPE_ARP) {
           auto arpPacket = ethPk->peekAtFront<ArpPacket>();
           match.OFB_IP_PROTO = arpPacket->getOpcode();
           match.OFB_IPV4_SRC = arpPacket->getSrcIpAddress();
           match.OFB_IPV4_DST = arpPacket->getDestIpAddress();
       }
       msg->setMatch(match);// 6 Byte
       msg->setChunkLength(B(24));
       msg->getHeaderForUpdate().length = 24;
       pk->insertAtFront(msg);
   }

   return pk;
}

Packet* OF100MessageFactory::createPacketOut(uint32_t* outports, int n_outports, int in_port, uint32_t buffer_id, Packet *ethPk) {
    auto msg = makeShared<OFP_Packet_Out>();
    auto pk = new Packet("packetOut");

    //create header 8 Byte
    msg->getHeaderForUpdate().version = OFP_VERSION;
    msg->getHeaderForUpdate().type = OFPT_PACKET_OUT;

    msg->setBuffer_id(buffer_id); // 4 Byte
    msg->setIn_port(in_port); // 2 Byte
    // actions_len 2 Byte

    msg->setActionsArraySize(n_outports); // 4 Byte per output action.
    for(int i=0; i<n_outports; i++) {
        ofp_action_output* action_output = new ofp_action_output();
        action_output->port = outports[i];
        msg->setActions(i, *action_output);
    }

    msg->setChunkLength(B(16 + 4*n_outports));

    if (buffer_id == OFP_NO_BUFFER)
    {   //No Buffer so send full frame.
        if(ethPk){
            // msg->encapsulate(frame->dup());
            pk->insertAtFront(ethPk->peekData());
        } else {
            throw cRuntimeError("OF100MessageFactory::createPacketOut: OFP_NO_BUFFER was set but no frame was provided.");
        }
    }
    msg->getHeaderForUpdate().length = B(msg->getChunkLength()).get() + pk->getByteLength();
    pk->insertAtFront(msg);
    return pk;
}

} /* namespace openflow */
