
cplusplus {{
    #include "inet/linklayer/ethernet/EtherFrame_m.h"
    #include "openflow/hyperflow/HyperFlowStructs.h"
    namespace openflow{
    typedef std::list<ControlChannelEntry> ControlChannel;
    typedef std::list<DataChannelEntry> DataChannel;
    } /*end namespace openflow*/
    
}};

class noncobject openflow::ControlChannel;
class noncobject openflow::DataChannel;   

namespace openflow;

// When packets are received by the data plane and sent to the connected controller,
// the OFP_PACKET_IN messages are used. If the complete packet needs to be sent to the controller, because it can not be
// stored in the bufer, it is encapsulated in the packet-in message.
packet HF_SyncReply{
    ControlChannel controlChannel;
    DataChannel dataChannel;
}