
import openflow.messages.HF_Packet;

cplusplus {{
    #include "openflow/hyperflow/HyperFlowStructs.h"
    namespace openflow{
        typedef std::list<ControlChannelEntry> ControlChannel;
        typedef std::list<DataChannelEntry> DataChannel;
    } 
}};

namespace openflow;

class ControlChannel
{
    @existingClass;
    @opaque;
//    @toString(.str());
}

class DataChannel
{
    @existingClass;
    @opaque;
//    @toString(.str());
}

// When packets are received by the data plane and sent to the connected controller,
// the OFP_PACKET_IN messages are used. If the complete packet needs to be sent to the controller, because it can not be
// stored in the bufer, it is encapsulated in the packet-in message.
class HF_SyncReply extends HF_Packet
{
    ControlChannel controlChannel;
    DataChannel dataChannel;
}
