
import inet.linklayer.ethernet.EtherFrame;

cplusplus {{
//    #include "inet/linklayer/ethernet/EtherFrame_m.h"
    #include "openflow/openflow/controller/Switch_Info.h"    
    namespace openflow{
    typedef std::list<Switch_Info *> SwitchInfoList;
    } /*end namespace openflow*/
}};

class openflow::SwitchInfoList {
	    @existingClass;
	    @opaque;
	    @descriptor(false);
}   

namespace openflow;

// When packets are received by the data plane and sent to the connected controller,
// the OFP_PACKET_IN messages are used. If the complete packet needs to be sent to the controller, because it can not be
// stored in the bufer, it is encapsulated in the packet-in message.
packet HF_ReportIn{
    string controllerId;
    SwitchInfoList switchInfoList; 
}