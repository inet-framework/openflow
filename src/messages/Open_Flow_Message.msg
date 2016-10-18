

cplusplus {{
    #include "openflow.h"
}};

struct ofp_header;

// base class for all OpenFlow protocol messages; only contains the OpenFlow header
packet Open_Flow_Message
{
    ofp_header header;
    
}