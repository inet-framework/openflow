
import openflow.messages.Open_Flow_Message;
import inet.linklayer.ethernet.EtherFrame;


namespace openflow;

//When the controller decides to send a packet out through the data plane, it uses the
//OFP PACKET OUT message.
packet OFP_Packet_Out extends Open_Flow_Message
{
	uint32_t buffer_id; // ID assigned by datapath (OFP_NO_BUFFER
                        //if none). 
	uint32_t in_port; // Packet���s input port or OFPP_CONTROLLER. 

	ofp_action_output actions[]; // Action list. 
//	 EthernetIIFrame frame;
// this is only a placeholder and has never been used
//	 uint8_t data[0];   // Packet data. The length is inferred
							//from the length field in the header.
							//(Only meaningful if buffer_id == -1.) 
}