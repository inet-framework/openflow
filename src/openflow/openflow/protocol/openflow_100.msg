
import inet.linklayer.common.MacAddress;
import inet.networklayer.contract.ipv4.Ipv4Address;

namespace openflow;

// Fields to match against flows
struct oxm_basic_match {
    uint16_t OFB_IN_PORT;          // Input switch port.

    inet::MacAddress OFB_ETH_SRC; // Ethernet source address.
    inet::MacAddress OFB_ETH_DST; // Ethernet destination address.
    uint16_t OFB_VLAN_VID;          // Input VLAN id.
    uint8_t OFB_VLAN_PCP;       // Input VLAN priority.
    //uint8_t pad1[1];           // Align to 64-bits
    uint16_t OFB_ETH_TYPE;          // Ethernet frame type.

    uint8_t OFB_IP_DSCP;            // IP ToS (actually DSCP field, 6 bits).
    uint8_t OFB_IP_PROTO;          // IP protocol or lower 8 bits of
    //uint8_t pad2[2];           // Align to 64-bits
    inet::Ipv4Address OFB_IPV4_SRC;           // IP source address.
    inet::Ipv4Address OFB_IPV4_DST;           // IP destination address.

    uint16_t OFB_TP_SRC;           // TCP/UDP source port.
    uint16_t OFB_TP_DST;           // TCP/UDP destination port.

    //from old implementation
    int OFB_ARP_OP; // ARP opcode.
    inet::Ipv4Address OFB_ARP_SPA; // ARP source IPv4 address.
    inet::Ipv4Address OFB_ARP_TPA; // ARP target IPv4 address.
    inet::MacAddress OFB_ARP_SHA; // ARP source hardware address.
    inet::MacAddress OFB_ARP_THA; // ARP target hardware address.

    uint32_t wildcards;        // Wildcard fields.
};
cplusplus(oxm_basic_match) {{
        int getPriority();
}}

// Fields to match against flows
struct ofp_match {
    uint16_t type; // One of OFPMT_*
    uint16_t length; // Length of ofp_match (excluding padding)
    // Followed by:
    // * -Exactly (length - 4) (possibly 0) bytes containing OXM TLVs,then
    // * -Exactly ((length+7)/8*8-length)(between 0 and 7) bytes of
    // * all-zerobytes
    // * In summary, ofp_match is padded as needed, to make its overall size
    // * a multiple of 8, to preserve alignement in structures using it.
    uint8_t oxm_fields[4]; // OXMs start here - Make compiler happy
};

// The match type indicates the match structure (set of fields that compose the
// * match) in use. The match type is placed in the type field at the beginning
// * of all match structures. The "OpenFlow Extensible Match" type corresponds
// * to OXM TLV format described below and must be supported by all OpenFlow
// * switches. Extensions that define other match types may be published on the
// * ONF wiki. Support for extensions is optional.
enum ofp_match_type {
    OFPMT_STANDARD = 0; // Deprecated.
    OFPMT_OXM = 1; // OpenFlow Extensible Match
};

// OXM Class IDs.
// * The high order bit differentiate reserved classes from member classes.
// * Classes 0x0000 to 0x7FFF are member classes, allocated by ONF.
// * Classes 0x8000 to 0xFFFE are reserved classes, reserved for standardisation.
enum ofp_oxm_class {
    OFPXMC_NXM_0 = 0x0000; // Backward compatibility with NXM
    OFPXMC_NXM_1 = 0x0001; // Backward compatibility with NXM
    OFPXMC_OPENFLOW_BASIC = 0x8000; // Basic class for OpenFlow
    OFPXMC_EXPERIMENTER = 0xFFFF; // Experimenter class
};

// OXM Flow match field types for OpenFlow basic class.
enum oxm_ofb_match_fields {
    OFPXMT_OFB_IN_PORT = 0; // Switch input port.
    OFPXMT_OFB_IN_PHY_PORT = 1; // Switch physical input port.
    OFPXMT_OFB_METADATA = 2; // Metadata passed between tables.
    OFPXMT_OFB_ETH_DST = 3; // Ethernet destination address.
    OFPXMT_OFB_ETH_SRC = 4; // Ethernet source address.
    OFPXMT_OFB_ETH_TYPE = 5; // Ethernet frame type.
    OFPXMT_OFB_VLAN_VID = 6; // VLAN id.
    OFPXMT_OFB_VLAN_PCP = 7; // VLAN priority.
    OFPXMT_OFB_IP_DSCP = 8; // IP DSCP (6 bits in ToS field).
    OFPXMT_OFB_IP_ECN = 9; // IP ECN (2 bits in ToS field).
    OFPXMT_OFB_IP_PROTO = 10; // IP protocol.
    OFPXMT_OFB_IPV4_SRC = 11; // IPv4 source address.
    OFPXMT_OFB_IPV4_DST = 12; // IPv4 destination address.
    OFPXMT_OFB_TCP_SRC = 13; // TCP source port.
    OFPXMT_OFB_TCP_DST = 14; // TCP destination port.
    OFPXMT_OFB_UDP_SRC = 15; // UDP source port.
    OFPXMT_OFB_UDP_DST = 16; // UDP destination port.
    OFPXMT_OFB_SCTP_SRC = 17; // SCTP source port.
    OFPXMT_OFB_SCTP_DST = 18; // SCTP destination port.
    OFPXMT_OFB_ICMPV4_TYPE = 19; // ICMP type.
    OFPXMT_OFB_ICMPV4_CODE = 20; // ICMP code.
    OFPXMT_OFB_ARP_OP = 21; // ARP opcode.
    OFPXMT_OFB_ARP_SPA = 22; // ARP source IPv4 address.
    OFPXMT_OFB_ARP_TPA = 23; // ARP target IPv4 address.
    OFPXMT_OFB_ARP_SHA = 24; // ARP source hardware address.
    OFPXMT_OFB_ARP_THA = 25; // ARP target hardware address.
    OFPXMT_OFB_IPV6_SRC = 26; // IPv6 source address.
    OFPXMT_OFB_IPV6_DST = 27; // IPv6 destination address.
    OFPXMT_OFB_IPV6_FLABEL = 28; // IPv6 Flow Label
    OFPXMT_OFB_ICMPV6_TYPE = 29; // ICMPv6 type.
    OFPXMT_OFB_ICMPV6_CODE = 30; // ICMPv6 code.
    OFPXMT_OFB_IPV6_ND_TARGET = 31; // Target address for ND.
    OFPXMT_OFB_IPV6_ND_SLL = 32; // Source link-layer for ND.
    OFPXMT_OFB_IPV6_ND_TLL = 33; // Target link-layer for ND.
    OFPXMT_OFB_MPLS_LABEL = 34; // MPLS label.
    OFPXMT_OFB_MPLS_TC = 35; // MPLS TC.
};

enum ofp_type {
    // Immutable messages.
    OFPT_HELLO = 0; // Symmetric message
    OFPT_ERROR = 1; // Symmetric message
    OFPT_ECHO_REQUEST = 2; // Symmetric message
    OFPT_ECHO_REPLY = 3; // Symmetric message
    OFPT_VENDOR = 4; // Symmetric message

    // Switch configuration messages.
    OFPT_FEATURES_REQUEST = 5; // Controller/switch message
    OFPT_FEATURES_REPLY = 6; // Controller/switch message
    OFPT_GET_CONFIG_REQUEST = 7; // Controller/switch message
    OFPT_GET_CONFIG_REPLY = 8; // Controller/switch message
    OFPT_SET_CONFIG = 9; // Controller/switch message

    // Asynchronous messages.
    OFPT_PACKET_IN = 10; // Async message
    OFPT_FLOW_REMOVED = 11; // Async message
    OFPT_PORT_STATUS = 12; // Async message

    // Controller command messages.
    OFPT_PACKET_OUT = 13; // Controller/switch message
    OFPT_FLOW_MOD = 14; // Controller/switch message
    OFPT_PORT_MOD = 15; // Controller/switch message
    // Statistics messages.
    OFPT_STATS_REQUEST = 16; // Controller/switch message
    OFPT_STATS_REPLY = 17; // Controller/switch message

    // Barrier messages.
    OFPT_BARRIER_REQUEST = 18; // Controller/switch message
    OFPT_BARRIER_REPLY = 19; // Controller/switch message

    // Queue Configuration messages.
    OFPT_QUEUE_GET_CONFIG_REQUEST = 20; // Controller/switch message
    OFPT_QUEUE_GET_CONFIG_REPLY = 21; // Controller/switch message
};

struct ofp_header {
    uint8_t version; // OFP_VERSION.
    uint8_t type; // One of the OFPT_ constants.
    uint16_t length; // Length including this ofp_header.
    uint32_t xid; // Transaction id associated with this packet.
     // Replies use the same id as was in the request
     // to facilitate pairing.
};

// Why is this packet being sent to the controller?
enum ofp_packet_in_reason {
    OFPR_NO_MATCH = 0; // No matching flow.
    OFPR_ACTION = 1; // Action explicitly output to controller.
    OFPR_INVALID_TTL = 2; // Packet has invalid TTL
};

// Send packet (controller -> datapath).
struct ofp_action_header {
    uint16_t type; // One of OFPAT_*.
    uint16_t len; // Length of action, including this
     // header.  This is the length of action,
     // including any padding to make it
     // 64-bit aligned.
    uint8_t pad[4];
//protected:
//    virtual void doNothing();
};

// Action structure for OFPAT_OUTPUT, which sends packets out port.
// When the port is the OFPP_CONTROLLER, max_len indicates the max
// number of bytes to send. A max_len of zero means no bytes of the
// packet should be sent. A max_len of OFPCML_NO_BUFFER means that
// the packet is not buffered and the complete packet is to be sent to
// the controller. */
struct ofp_action_output extends ofp_action_header {
    // len = 16;
    uint32_t port; // Output port.
    string creationModule;
};

// Packet received on port (datapath -> controller).
struct ofp_packet_in {
    ofp_header header;
    uint32_t buffer_id; // ID assigned by datapath.
    uint16_t total_len; // Full length of frame.
    uint8_t reason; // Reason packet is being sent (one of OFPR_*)
    uint8_t table_id; // ID of the table that was looked up
    oxm_basic_match match; // Packet metadata. Variable size.
    // Followed by:
     // * -Exactly2all-zeropaddingbytes,then
     // * -AnEthernetframewhoselengthisinferredfromheader.length.
     // * The padding bytes preceding the Ethernet frame ensure that the IP
     // * header (if any) following the Ethernet header is 32-bit aligned.
    uint8_t pad[2]; // Align to 64 bit + 16 bit

    // uint8_t data[0]; // Ethernet frame
};

struct ofp_packet_out {
    ofp_header header;
    uint32_t buffer_id; // ID assigned by datapath (OFP_NO_BUFFER if none).
    uint32_t in_port; // Packet�s input port or OFPP_CONTROLLER.
    uint16_t actions_len; // Size of action array in bytes.
    uint8_t pad[6];
    // ofp_action_header actions[0]; // Action list.
    // uint8_t data[0]; // Packet data. The length is inferred from the length field in the header. (Only meaningful if buffer_id == -1.)
};

