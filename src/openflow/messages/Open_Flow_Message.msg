

cplusplus {{
    #include "openflow/openflow/protocol/OpenFlow.h"
}};

class openflow::ofp_header extends void;

namespace openflow;

// base class for all OpenFlow protocol messages; only contains the OpenFlow header
packet Open_Flow_Message
{
    ofp_header header;
    
}