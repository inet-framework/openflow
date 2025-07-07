

import openflow.messages.HF_Packet;

cplusplus {{
    #include "openflow/hyperflow/HyperFlowStructs.h"
}};

namespace openflow;

class Switch_Info
{
    @existingClass;
    @descriptor(readonly);
    int connId;
    int version;
    //std::string macAddress;
    int numOfPorts; //TODO idPort vector
    // TcpSocket* socket;
    int indexPort[] @sizeGetter(getNumOfPorts);
}

class ControlChannelEntry
{
    @existingClass;
    @descriptor(readonly);
	// std::list<Switch_Info *> switches; // TODO add this variable to descriptor
    string controllerId;
    simtime_t time;
}

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
