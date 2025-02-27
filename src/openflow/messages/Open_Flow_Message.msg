
import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import openflow.messages.OpenFlowStructs; 

cplusplus {{
    #include "openflow/openflow/protocol/OpenFlow.h"
    
    namespace openflow{
        inline std::ostream& operator<<(std::ostream& os, ofp_action_output& action)
        {
    		os << "Port (hex): " << std::hex << action.port << endl;
    		return os;
    	}
    	
        inline std::ostream& operator<<(std::ostream& os, oxm_basic_match& match)
        {
        	os << "OFB_ETH_TYPE: " << std::hex << match.OFB_ETH_TYPE << ", OFB_ETH_SRC: " << match.OFB_ETH_SRC;
        	os << ", OFB_ETH_DST: " << match.OFB_ETH_DST << ", OFB_IN_PORT: " << match.OFB_IN_PORT << endl; 
    		os << ", OFB_ARP_OP: " << match.OFB_ARP_OP << ", OFB_ARP_SHA: " << match.OFB_ARP_SHA;
    		os << ", OFB_ARP_THA: " << match.OFB_ARP_THA << ", OFB_ARP_SPA: " << match.OFB_ARP_SPA;
    		os << ", OFB_ARP_TPA: " << match.OFB_ARP_TPA << endl;
    		return os;
    	}
	} /*end namespace openflow*/
}};


namespace openflow;

class ofp_header {
	    @existingClass;
	    @opaque;
	    @descriptor(false);
}

struct oxm_basic_match {
	    @existingClass;
	    @opaque;
	    @descriptor(false);
}

struct ofp_action_output {
	    @existingClass;
	    @opaque;
	    @descriptor(false);
}

// base class for all OpenFlow protocol messages; only contains the OpenFlow header
class Open_Flow_Message extends inet::FieldsChunk 
{
    ofp_header header;
}
