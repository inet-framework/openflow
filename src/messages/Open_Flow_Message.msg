

cplusplus {{
    #include "openflow.h"
}};

class ofp_header extends void;

// base class for all OpenFlow protocol messages; only contains the OpenFlow header
packet Open_Flow_Message
{
    ofp_header header;
    
}