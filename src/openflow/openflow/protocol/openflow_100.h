

#ifndef OPENFLOW__OPENFLOW_PROTOCOL_OPENFLOW_H_
#define OPENFLOW__OPENFLOW_PROTOCOL_OPENFLOW_H_


#define OFP_VERSION   0x01
#define OFP_MAX_PORT_NAME_LEN 16
#define OFP_ETH_ALEN 6

#include "inet/linklayer/common/MacAddress.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"

#include "openflow/openflow/protocol/openflow_100_m.h"

using namespace inet;

namespace openflow{

// Flow wildcards.
enum ofp_flow_wildcards {
    OFPFW_IN_PORT = 1 << 0, // Switch input port.
    OFPFW_DL_VLAN = 1 << 1, // VLAN id.
    OFPFW_DL_SRC = 1 << 2, // Ethernet source address.
    OFPFW_DL_DST = 1 << 3, // Ethernet destination address.
    OFPFW_DL_TYPE = 1 << 4, // Ethernet frame type.
    OFPFW_NW_PROTO = 1 << 5, // IP protocol.
    OFPFW_TP_SRC = 1 << 6, // TCP/UDP source port.
    OFPFW_TP_DST = 1 << 7, // TCP/UDP destination port.
    // IP source address wildcard bit count.  0 is exact match, 1 ignores the
     // * LSB, 2 ignores the 2 least-significant bits, ..., 32 and higher wildcard
     // * the entire field.  This is the *opposite* of the usual convention where
     // * e.g. /24 indicates that 8 bits (not 24 bits) are wildcarded.
    OFPFW_NW_SRC_SHIFT = 8,
    OFPFW_NW_SRC_BITS = 6,
    OFPFW_NW_SRC_MASK = ((1 << OFPFW_NW_SRC_BITS) - 1) << OFPFW_NW_SRC_SHIFT,
    OFPFW_NW_SRC_ALL = 32 << OFPFW_NW_SRC_SHIFT,

    // IP destination address wildcard bit count.  Same format as source.
    OFPFW_NW_DST_SHIFT = 14,
    OFPFW_NW_DST_BITS = 6,
    OFPFW_NW_DST_MASK = ((1 << OFPFW_NW_DST_BITS) - 1) << OFPFW_NW_DST_SHIFT,
    OFPFW_NW_DST_ALL = 32 << OFPFW_NW_DST_SHIFT,

    OFPFW_DL_VLAN_PCP = 1 << 20, // VLAN priority.
    OFPFW_NW_TOS = 1 << 21, // IP ToS (DSCP field, 6 bits).

    // Wildcard all fields.
    OFPFW_ALL = ((1 << 22) - 1),
};

inline bool operator==(const oxm_basic_match &m1, const oxm_basic_match& m2) {
    return m2.OFB_IN_PORT == m1.OFB_IN_PORT
            && m2.OFB_ETH_DST == m1.OFB_ETH_DST
            && m2.OFB_ETH_SRC == m1.OFB_ETH_SRC
            && m2.OFB_ETH_TYPE == m1.OFB_ETH_TYPE
            && m2.OFB_ARP_OP == m1.OFB_ARP_OP
            && m2.OFB_ARP_SHA == m1.OFB_ARP_SHA
            && m2.OFB_ARP_SPA == m1.OFB_ARP_SPA
            && m2.OFB_ARP_THA == m1.OFB_ARP_THA
            && m2.OFB_ARP_TPA == m1.OFB_ARP_TPA;
}

struct oxm_tlv {
    uint16_t oxm_class; /* One of ofp_oxm_class */
    uint8_t oxm_field; /* One of oxm_ofb_match_fields */
    bool oxm_hasmask;
    uint8_t oxm_length;
    void *value;
};

const uint32_t OFP_NO_BUFFER = 0xffffffff;

/* Flow setup and teardown (controller -> datapath). */

enum ofp_flow_mod_command {
    OFPFC_ADD = 0, /* New flow. */
    OFPFC_MODIFY = 1, /* Modify all matching flows. */
    OFPFC_MODIFY_STRICT = 2, /* Modify entry strictly matching wildcards and
     priority. */
    OFPFC_DELETE = 3, /* Delete all matching flows. */
    OFPFC_DELETE_STRICT = 4,
/* Delete entry strictly matching wildcards and
 priority. */
};



/* Description of a port */
struct ofp_port {
    uint32_t port_no;
    //uint8_t pad[4];
    uint8_t hw_addr[OFP_ETH_ALEN];
    //uint8_t pad2[2];                  /* Align to 64 bits. */
    char name[OFP_MAX_PORT_NAME_LEN]; /* Null-terminated */
    uint32_t config;        /* Bitmap of OFPPC_* flags. */
    uint32_t state;         /* Bitmap of OFPPS_* flags. */
    /* Bitmaps of OFPPF_* that describe features.  All bits zeroed if
    * unsupported or unavailable. */
    uint32_t curr;          /* Current features. */
    uint32_t advertised;    /* Features being advertised by the port. */
    uint32_t supported;     /* Features supported by the port. */
    uint32_t peer;          /* Features advertised by peer. */
    uint32_t curr_speed;    /* Current port bitrate in kbps. */
    uint32_t max_speed;     /* Max port bitrate in kbps */
    int interfaceId = -1;
    cModule *mac = nullptr;
};

enum ofp_port_config {
    OFPPC_PORT_DOWN    = 1 << 0,  /* Port is administratively down. */
    OFPPC_NO_RECV      = 1 << 2,  /* Drop all packets received by port. */
    OFPPC_NO_FWD       = 1 << 5,  /* Drop packets forwarded to port. */
    OFPPC_NO_PACKET_IN = 1 << 6   /* Do not send packet-in msgs for port. */
};

enum ofp_port_state {
    OFPPS_LINK_DOWN    = 1 << 0,  /* No physical link present. */
    OFPPS_BLOCKED      = 1 << 1,  /* Port is blocked */
    OFPPS_LIVE         = 1 << 2,  /* Live for Fast Failover Group. */
};


enum ofp_port_no {
    /* Maximum number of physical and logical switch ports. */
    OFPP_MAX        = 0xffffff00,
    /* Reserved OpenFlow Port (fake output "ports"). */
    OFPP_IN_PORT    = 0xfffffff8,  /* Send the packet out the input port.  This
    reserved port must be explicitly used
    in order to send back out of the input
    port. */
    OFPP_TABLE      = 0xfffffff9,  /* Submit the packet to the first flow table
    NB: This destination port can only be
    used in packet-out messages. */
    OFPP_NORMAL     = 0xfffffffa,  /* Process with normal L2/L3 switching. */
    OFPP_FLOOD      = 0xfffffffb,  /* All physical ports in VLAN, except input
    port and those blocked or link down. */
    OFPP_ALL        = 0xfffffffc,  /* All physical ports except input port. */
    OFPP_CONTROLLER = 0xfffffffd,  /* Send to controller. */
    OFPP_LOCAL      = 0xfffffffe,  /* Local openflow "port". */
    OFPP_ANY        = 0xffffffff   /* Wildcard port used only for flow mod
    (delete) and flow stats requests. Selects
    all flows regardless of output port
    (including flows with no output port). */
};

/* Features of ports available in a datapath. */
enum ofp_port_features {
    OFPPF_10MB_HD    = 1 << 0,  /* 10 Mb half-duplex rate support. */
    OFPPF_10MB_FD    = 1 << 1,  /* 10 Mb full-duplex rate support. */
    OFPPF_100MB_HD   = 1 << 2,  /* 100 Mb half-duplex rate support. */
    OFPPF_100MB_FD   = 1 << 3,  /* 100 Mb full-duplex rate support. */
    OFPPF_1GB_HD     = 1 << 4,  /* 1 Gb half-duplex rate support. */
    OFPPF_1GB_FD     = 1 << 5,  /* 1 Gb full-duplex rate support. */
    OFPPF_10GB_FD    = 1 << 6,  /* 10 Gb full-duplex rate support. */
    OFPPF_40GB_FD    = 1 << 7,  /* 40 Gb full-duplex rate support. */
    OFPPF_100GB_FD   = 1 << 8,  /* 100 Gb full-duplex rate support. */
    OFPPF_1TB_FD     = 1 << 9,  /* 1 Tb full-duplex rate support. */
    OFPPF_OTHER      = 1 << 10, /* Other rate, not in the list. */
    OFPPF_COPPER     = 1 << 11, /* Copper medium. */
    OFPPF_FIBER      = 1 << 12, /* Fiber medium. */
    OFPPF_AUTONEG    = 1 << 13, /* Auto-negotiation. */
    OFPPF_PAUSE      = 1 << 14, /* Pause. */
    OFPPF_PAUSE_ASYM = 1 << 15  /* Asymmetric pause. */
};

} /*end namespace openflow*/

#endif /* OPENFLOW__OPENFLOW_PROTOCOL_OPENFLOW_H_ */
