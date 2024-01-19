//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// c Timo Haeckel, for HAW Hamburg
//


#include "openflow/openflow/protocol/OF100MatchBuilder.h"

namespace openflow {



OFMatchBuilder* OF100MatchBuilder::setField(oxm_ofb_match_fields field, void* value){
    //interpret the field, cast & set the value, update wildcard.
    switch (field){
    case OFPXMT_OFB_IN_PORT:
        match.OFB_IN_PORT = *static_cast<int*>(value);
        match.wildcards &= ~OFPFW_IN_PORT;
        break;
    case OFPXMT_OFB_ETH_SRC:
        match.OFB_ETH_SRC = *static_cast<inet::MACAddress*>(value);
        match.wildcards &= ~OFPFW_DL_SRC;
        break;
    case OFPXMT_OFB_ETH_DST:
        match.OFB_ETH_DST = *static_cast<inet::MACAddress*>(value);
        match.wildcards &= ~OFPFW_DL_DST;
        break;
    case OFPXMT_OFB_VLAN_VID:
        match.OFB_VLAN_VID = *static_cast<uint16_t*>(value);
        match.wildcards &= ~OFPFW_DL_VLAN;
        break;
    case OFPXMT_OFB_VLAN_PCP:
        match.OFB_VLAN_PCP = *static_cast<uint8_t*>(value);
        match.wildcards &= ~OFPFW_DL_VLAN_PCP;
        break;
    case OFPXMT_OFB_ETH_TYPE:
        match.OFB_ETH_TYPE = *static_cast<uint16_t*>(value);
        match.wildcards &= ~OFPFW_DL_TYPE;
        break;
    case OFPXMT_OFB_IP_DSCP:
        match.OFB_IP_DSCP = *static_cast<uint8_t*>(value);
        match.wildcards &= ~OFPFW_NW_TOS;
        break;
    case OFPXMT_OFB_IP_PROTO:
        match.OFB_IP_PROTO = *static_cast<uint8_t*>(value);
        match.wildcards &= ~OFPFW_NW_PROTO;
        break;
    case OFPXMT_OFB_IPV4_SRC:
        match.OFB_IPV4_SRC = *static_cast<inet::IPv4Address*>(value);
        match.wildcards &= ~OFPFW_NW_SRC_ALL;
        break;
    case OFPXMT_OFB_IPV4_DST:
        match.OFB_IPV4_DST = *static_cast<inet::IPv4Address*>(value);
        match.wildcards &= ~OFPFW_NW_DST_ALL;
        break;
    case OFPXMT_OFB_TCP_SRC:
        match.OFB_TP_SRC = *static_cast<uint16_t*>(value);
        match.wildcards &= ~OFPFW_TP_SRC;
        break;
    case OFPXMT_OFB_TCP_DST:
        match.OFB_TP_DST = *static_cast<uint16_t*>(value);
        match.wildcards &= ~OFPFW_TP_DST;
        break;
    case OFPXMT_OFB_UDP_SRC:
        match.OFB_TP_SRC = *static_cast<uint16_t*>(value);
        match.wildcards &= ~OFPFW_TP_SRC;
        break;
    case OFPXMT_OFB_UDP_DST:
        match.OFB_TP_DST = *static_cast<uint16_t*>(value);
        match.wildcards &= ~OFPFW_TP_DST;
        break;
    case OFPXMT_OFB_ARP_OP:
        match.OFB_ARP_OP = *static_cast<int*>(value);
        break;
    case OFPXMT_OFB_ARP_SPA:
        match.OFB_ARP_SPA = *static_cast<inet::IPv4Address*>(value);
        break;
    case OFPXMT_OFB_ARP_TPA:
        match.OFB_ARP_TPA = *static_cast<inet::IPv4Address*>(value);
        break;
    case OFPXMT_OFB_ARP_SHA:
        match.OFB_ARP_SHA = *static_cast<inet::MACAddress*>(value);
        break;
    case OFPXMT_OFB_ARP_THA:
        match.OFB_ARP_THA = *static_cast<inet::MACAddress*>(value);
        break;
    default:
        throw cRuntimeError("This field is not supported by the current match implementation!");
        break;
    }

    return this;
}


} /* namespace openflow */
