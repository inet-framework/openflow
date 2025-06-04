
#include <inet/common/INETDefs.h>

#define OFP_100 0x01
#define OFP_135 0x04 //currently not supported.
#define OFP_141 0x05 //currently not supported.
#define OFP_151 0x06 //currently not supported.

#if INET_VERSION < 0x0403 || INET_VERSION == 0x0403 && INET_PATCH_LEVEL < 0x02
#error OpenFlow: Incompatible INET version. At least INET version v4.3.2 required.
#endif

#ifndef OFP_VERSION_IN_USE
    #define OFP_VERSION_IN_USE OFP_100
#endif

//#if OFP_VERSION_IN_USE == OFP_100
    #include <openflow/openflow/protocol/openflow_100.h>
//#elif OFP_VERSION_IN_USE == OFP_135
////TODO add implementation for ofp135
//    #include <openflow/openflow/protocol/openflow_135.h>
//
//#elif OFP_VERSION_IN_USE == OFP_141
////TODO add implementation for ofp141
//    #include <openflow/openflow/protocol/openflow_141.h>
//
//#elif OFP_VERSION_IN_USE == OFP_151
////TODO add implementation for ofp151
//    #include <openflow/openflow/protocol/openflow_151.h>
//
//#endif
//

