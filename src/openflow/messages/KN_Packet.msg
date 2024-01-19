
import inet.linklayer.ethernet.EtherFrame;

cplusplus {{
    #include "openflow/utility/KandooStructs.h"
}};
  
struct openflow::KandooEntry {
	    @existingClass;
	    @opaque;
	    @descriptor(false);
}
  
namespace openflow;

// When packets are received by the data plane and sent to the connected controller,
// the OFP_PACKET_IN messages are used. If the complete packet needs to be sent to the controller, because it can not be
// stored in the bufer, it is encapsulated in the packet-in message.
packet KN_Packet{
    KandooEntry knEntry;
}