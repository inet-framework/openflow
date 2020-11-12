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


#ifndef OPENFLOW_OPENFLOW_UTIL_OFMESSAGEFACTORY_H_
#define OPENFLOW_OPENFLOW_UTIL_OFMESSAGEFACTORY_H_

#include <openflow/openflow/protocol/OpenFlow.h>
#include <string>

namespace openflow {
class OFP_Features_Reply;
class OFP_Features_Request;
class OFP_Hello;
class OFP_Packet_In;
class OFP_Packet_Out;
class OFP_Flow_Mod;
} /* namespace openflow */

namespace inet {
class EthernetIIFrame;
} /* namespace inet */

namespace openflow {

/**
 * Class for static OFMessageFactory creation.
 * Provides access to a message factory for the openflow version currently in use.
 *
 * @author Timo Haeckel, for HAW Hamburg
 */
class OFMessageFactory {

public:
    /**
     * Provides an instance of OFMessageFactory for the currently used version.
     * @return Reference to the factory.
     */
    static OFMessageFactory* instance();

protected:
    OFMessageFactory(){}
    virtual ~OFMessageFactory(){}

public:
    /**
     * Create an OFP_Features_Reply message.
     * @param dpid          The switche ID / MAC Address
     * @param n_buffers     Number of Buffers available in the switch.
     * @param n_tables      Number of Tables available in the switch.
     * @param capabilities  Capabilities flags
     * @param n_ports       Number of Ports.
     * @return              The created message.
     */
    virtual OFP_Features_Reply* createFeaturesReply(std::string dpid, uint32_t n_buffers, uint8_t n_tables, uint32_t capabilities, uint32_t n_ports = 0) = 0;

    /**
     * Create an OFP_Features_Request message.
     * @return              The created message.
     */
    virtual OFP_Features_Request* createFeatureRequest() = 0;

    /**
     * Create an OFP_Flow_Mod message.
     * @param mod_com       The command of the modification.
     * @param match         The match to insert in the table.
     * @param pritority     The priority of this flow entry.
     * @param outports      The output ports for matching flows.
     * @param n_outports    Number of output ports.
     * @param idleTimeOut   The idle Timeout for the flow entry.
     * @param hardTimeOut   The hard Timeout for the flow entry.
     * @return              The created message.
     */
    virtual OFP_Flow_Mod* createFlowModMessage(ofp_flow_mod_command mod_com,const oxm_basic_match& match, int pritority, uint32_t* outports, int n_outports, uint32_t idleTimeOut=1 , uint32_t hardTimeOut=0) = 0;

    /**
     * Create an OFP_Hello message.
     * @return              The created message.
     */
    virtual OFP_Hello* createHello() = 0;

    /**
     * Create an OFP_Packet_In message.
     * @param reason        The reson why this packet is forwarded.
     * @param frame         The frame to encapsulate.
     * @param buffer_id     The buffer_id or OFP_NO_BUFFER if not buffered.
     * @param sendFullFrame True if the full frame should be transmitted.
     * @return              The created message.
     */
    virtual OFP_Packet_In* createPacketIn(ofp_packet_in_reason reason, inet::EthernetIIFrame *frame, uint32_t buffer_id = OFP_NO_BUFFER, bool sendFullFrame = true) = 0;

    /**
     * Create an OFP_Packet_Out message.
     * @param outports      The output ports for matching flows.
     * @param n_outports    Number of output ports.
     * @param in_port       The input port of the packet.
     * @param buffer_id     The buffer_id or OFP_NO_BUFFER if not buffered.
     * @param frame         The frame to encapsulate if not buffered.
     * @return              The created message.
     */
    virtual OFP_Packet_Out* createPacketOut(uint32_t* outports, int n_outports, int in_port, uint32_t buffer_id = OFP_NO_BUFFER, inet::EthernetIIFrame *frame = nullptr) = 0;
};

} /* namespace openflow */

#endif /* OPENFLOW_OPENFLOW_UTIL_OFMESSAGEFACTORY_H_ */
