
//import openflow.openflow.protocol.OpenFlow;
import openflow.messages.Open_Flow_Message;

namespace openflow;


//Upon session establishment, the controller sends an OFP Features Request message
//to get information about the capabilities of a switch. This message does
//not contain a body beyond the OpenFlow header. The switch responds with an
//OFP Features Reply message.
packet OFP_Features_Request extends Open_Flow_Message
{
}