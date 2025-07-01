

import openflow.messages.HF_Packet;

cplusplus {{
    #include "openflow/hyperflow/HyperFlowStructs.h"
}};

namespace openflow;

class DataChannelEntry
{
    @existingClass;
    @descriptor(readonly);
    string srcController;
    string trgSwitch;
    int eventId;
    cObject * payload;
}

// When packets are received by the data plane and sent to the connected controller,
// the OFP_PACKET_IN messages are used. If the complete packet needs to be sent to the controller, because it can not be
// stored in the bufer, it is encapsulated in the packet-in message.
class HF_ChangeNotification extends HF_Packet
{
    DataChannelEntry entry;
}
