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

#include "openflow/openflow/switch/flowtable/OF100_FlowTableEntry.h"
#include "openflow/openflow/protocol/OFMatchFactory.h"

#include "inet/linklayer/common/MacAddress.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include <string>
#include <sstream>

using namespace std;
using namespace inet;

namespace openflow {

OF100_FlowTableEntry::OF100_FlowTableEntry() {
    //init counters
}

OF100_FlowTableEntry::OF100_FlowTableEntry(OFP_Flow_Mod* flow_mod) : OF_FlowTableEntry(flow_mod){
    cookie = flow_mod->getCookie();
    flags = flow_mod->getFlags();
    match = flow_mod->getMatch();
    for (size_t i = 0 ; i < flow_mod->getActionsArraySize(); i++){
        instructions.push_back(flow_mod->getActions(i));
    }
}

OF100_FlowTableEntry::OF100_FlowTableEntry(omnetpp::cXMLElement* xmlDoc) : OF_FlowTableEntry(xmlDoc){
    //get attributes
    if(const char* value = xmlDoc->getAttribute("cookie"))
        cookie = atoi(value);//cookie
    if(const char* value = xmlDoc->getAttribute("flags"))
        flags = atoi(value);//flags

    auto builder = OFMatchFactory::getBuilder();
    if(cXMLElement* xmlMatch = xmlDoc->getFirstChildWithTag("match")){
        if (const char* value = xmlMatch->getAttribute("in_port"))
        {
            int parsedValue =  atoi(value);
            builder->setField(OFPXMT_OFB_IN_PORT, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("dl_src"))
        {
            MacAddress parsedValue = MacAddress(value);
            builder->setField(OFPXMT_OFB_ETH_SRC, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("dl_dst"))
        {
            MacAddress parsedValue = MacAddress(value);
            builder->setField(OFPXMT_OFB_ETH_DST, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("dl_vlan"))
        {
            uint16_t parsedValue = static_cast<uint16_t>(atoi(value));
            builder->setField(OFPXMT_OFB_VLAN_VID, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("dl_vlan_pcp"))
        {
            uint8_t parsedValue = static_cast<uint8_t>(atoi(value));
            builder->setField(OFPXMT_OFB_VLAN_PCP, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("dl_type"))
        {
            uint16_t parsedValue = static_cast<uint16_t>(atoi(value));
            builder->setField(OFPXMT_OFB_ETH_TYPE, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("nw_proto"))
        {
            uint8_t parsedValue = static_cast<uint8_t>(atoi(value));
            builder->setField(OFPXMT_OFB_IP_PROTO, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("nw_src"))
        {
            Ipv4Address parsedValue = Ipv4Address(value);
            builder->setField(OFPXMT_OFB_IPV4_SRC, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("nw_dst"))
        {
            Ipv4Address parsedValue = Ipv4Address(value);
            builder->setField(OFPXMT_OFB_IPV4_DST, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("tp_src"))
        {
            uint16_t parsedValue = static_cast<uint16_t>(atoi(value));
            builder->setField(OFPXMT_OFB_TCP_SRC, &parsedValue);
        }
        if (const char* value = xmlMatch->getAttribute("tp_dst"))
        {
            uint16_t parsedValue = static_cast<uint16_t>(atoi(value));
            builder->setField(OFPXMT_OFB_TCP_DST, &parsedValue);
        }

        match = builder->build();
        if (const char* value = xmlMatch->getAttribute("wildcards"))
        {
            // overrides calcualted wildcard with a static value.
            match.wildcards = static_cast<uint32_t>(stoul(value));
        }
    }

    //get instructions
    cXMLElement* xmlInstructions = xmlDoc->getFirstChildWithTag("instructions");
    cXMLElementList xmlInstructionList = xmlInstructions->getChildrenByTagName("action_output");
    for (size_t i=0; i<xmlInstructionList.size(); i++){
        ofp_action_output action;
        action.port = atoi(xmlInstructionList[i]->getAttribute("port"));
        instructions.push_back(action);
    }

}

OF100_FlowTableEntry::~OF100_FlowTableEntry() {
    instructions.clear();
}

bool OF100_FlowTableEntry::tryMatch(const OF_FlowTableEntry* other) {
    const OF100_FlowTableEntry* casted = dynamic_cast<const OF100_FlowTableEntry*> (other);
    if(casted->match.wildcards == this->match.wildcards) {
        return tryMatch(casted->match, casted->match.wildcards);
    }
    return false;
}

bool OF100_FlowTableEntry::tryMatch(const oxm_basic_match& other, bool intersectWildcards) {
    if(intersectWildcards)
    {
        return tryMatch(other, intersectWildCards(match.wildcards, other.wildcards));
    }
    return tryMatch(other, match.wildcards);
}

bool OF100_FlowTableEntry::tryMatch(const oxm_basic_match& other, uint32_t wildcards) {
    //debuggable
    bool port = ((wildcards & OFPFW_IN_PORT) || match.OFB_IN_PORT == other.OFB_IN_PORT) ;
    bool dl_type = ((wildcards & OFPFW_DL_TYPE) || match.OFB_ETH_TYPE == other.OFB_ETH_TYPE ) ;
    bool dl_src = ((wildcards & OFPFW_DL_SRC) || !match.OFB_ETH_SRC.compareTo(other.OFB_ETH_SRC)) ;
    bool dl_dst = ((wildcards & OFPFW_DL_DST) || !match.OFB_ETH_DST.compareTo(other.OFB_ETH_DST)) ;
    bool dl_vlan = ((wildcards & OFPFW_DL_VLAN) || match.OFB_VLAN_VID == other.OFB_VLAN_VID ) ;
    bool dl_vlan_pcb = ((wildcards & OFPFW_DL_VLAN_PCP) || match.OFB_VLAN_PCP == other.OFB_VLAN_PCP ) ;
    bool nw_proto = ((wildcards & OFPFW_NW_PROTO) || match.OFB_IP_PROTO == other.OFB_IP_PROTO ) ;
    bool nw_src = ((wildcards & OFPFW_NW_SRC_ALL) || match.OFB_IPV4_SRC.equals(other.OFB_IPV4_SRC) ) ;
    bool nw_dst = ((wildcards & OFPFW_NW_DST_ALL) || match.OFB_IPV4_DST.equals(other.OFB_IPV4_DST) ) ;
    bool tp_src = ((wildcards & OFPFW_TP_SRC) || match.OFB_TP_SRC == other.OFB_TP_SRC ) ;
    bool tp_dst = ((wildcards & OFPFW_TP_DST) || match.OFB_TP_DST == other.OFB_TP_DST ) ;
    return port && dl_type && dl_src && dl_dst && dl_vlan && dl_vlan_pcb && nw_proto && nw_src && nw_dst && tp_src && tp_dst;
//    return ((wildcards & OFPFW_IN_PORT) || match.OFB_IN_PORT == other.OFB_IN_PORT) &&
//        ((wildcards & OFPFW_DL_TYPE) || match.OFB_ETH_TYPE == other.OFB_ETH_TYPE ) &&
//        ((wildcards & OFPFW_DL_SRC) || !match.OFB_ETH_SRC.compareTo(other.OFB_ETH_SRC)) &&
//        ((wildcards & OFPFW_DL_DST) || !match.OFB_ETH_DST.compareTo(other.OFB_ETH_DST)) &&
//        ((wildcards & OFPFW_DL_VLAN) || match.OFB_VLAN_VID == other.OFB_VLAN_VID ) &&
//        ((wildcards & OFPFW_DL_VLAN_PCP) || match.OFB_VLAN_PCP == other.OFB_VLAN_PCP ) &&
//        ((wildcards & OFPFW_NW_PROTO) || match.OFB_IP_PROTO == other.OFB_IP_PROTO ) &&
//        ((wildcards & OFPFW_NW_SRC_ALL) || match.OFB_IPV4_SRC.equals(other.OFB_IPV4_SRC) ) &&
//        ((wildcards & OFPFW_NW_DST_ALL) || match.OFB_IPV4_DST.equals(other.OFB_IPV4_DST) ) &&
//        ((wildcards & OFPFW_TP_SRC) || match.OFB_TP_SRC == other.OFB_TP_SRC ) &&
//        ((wildcards & OFPFW_TP_DST) || match.OFB_TP_DST == other.OFB_TP_DST );
}

std::string OF100_FlowTableEntry::exportToXML() {
    std::ostringstream oss;
    string tab = "    ";
    oss << "<flowEntry";
    oss << " hardTimeout=\"" << hardTimeout << "\"";
    oss << " idleTimeout=\"" << idleTimeout << "\"";
    oss << " cookie=\"" << cookie << "\"";
    oss << " priority=\"" << priority << "\"";
    oss << " flags=\"" << flags << "\"";
    oss << " >" << endl;//end flow entry


    // oxm_basic_match match;
    uint32_t w = match.wildcards;
    oss << tab << "<match ";
    if(!(w & OFPFW_IN_PORT))
        oss << " in_port=\"" << (int)match.OFB_IN_PORT << "\""; //uint16_t in_port;
    if(!match.OFB_ETH_DST.isUnspecified() && !(w & OFPFW_DL_DST))
        oss << " dl_dst=\"" << match.OFB_ETH_DST.str() << "\""; //inet::MacAddress dl_src;
    if(!match.OFB_ETH_SRC.isUnspecified() && !(w & OFPFW_DL_SRC))
        oss << " dl_src=\"" << match.OFB_ETH_SRC.str() << "\""; //inet::MacAddress dl_dst;
    if(!(w & OFPFW_DL_VLAN))
        oss << " dl_vlan=\"" << (int)match.OFB_VLAN_VID << "\""; //uint16_t dl_vlan;
    if(!(w & OFPFW_DL_VLAN_PCP))
        oss << " dl_vlan_pcp=\"" << (int)match.OFB_VLAN_PCP << "\""; //uint8_t dl_vlan_pcp;
    if(!(w & OFPFW_DL_TYPE))
        oss << " dl_type=\"" << (int)match.OFB_ETH_TYPE << "\""; //uint16_t dl_type;
    if(!(w & OFPFW_NW_PROTO))
        oss << " nw_proto=\"" << (int)match.OFB_IP_PROTO << "\""; //uint8_t nw_proto;
    if(!match.OFB_IPV4_SRC.isUnspecified() && !(w & OFPFW_NW_SRC_ALL))
        oss << " nw_src=\"" << match.OFB_IPV4_SRC.str(false) << "\""; //inet::Ipv4Address nw_src;
    if(!match.OFB_IPV4_DST.isUnspecified() && !(w & OFPFW_NW_DST_ALL))
        oss << " nw_dst=\"" << match.OFB_IPV4_DST.str(false) << "\""; //inet::Ipv4Address nw_dst;
    if(!(w & OFPFW_TP_SRC))
        oss << " tp_src=\"" << (int)match.OFB_TP_SRC << "\""; //uint16_t tp_src;
    if(!(w & OFPFW_TP_DST))
        oss << " tp_dst=\"" << (int)match.OFB_TP_DST << "\""; //uint16_t tp_dst;

    oss << " wildcards=\"" << match.wildcards << "\""; //uint32_t wildcards;
    oss << " />" << endl;

    // std::vector<ofp_action_output> instructions;
    if(!instructions.empty()){
        oss << tab << "<instructions>" << endl;
        for (uint32_t i=0;i<instructions.size();i++){
            int port = instructions[i].port;
            oss << tab << tab << "<action_output port=\"" << port << "\"/>" << endl;
        }
        oss << tab << "</instructions>" << endl;
    }

    oss << "</flowEntry>" << endl;//end flow entry
    return oss.str();
}

std::string OF100_FlowTableEntry::print() const{
    ostringstream oss;
    string tab = "    ";
    oss << "OF100_FlowTableEntry{ ";
    oss << "cookie(" << cookie << ") ";
    oss << "priority(" << priority << ") ";
    oss << "flags(" << flags << ") ";
    oss << "creationTime(" << creationTime.str() << ") ";
    oss << "lastMatched(" << lastMatched.str() << ") ";
    oss << "hardTimeout(" << hardTimeout << ") ";
    oss << "idleTimeout(" << idleTimeout << ") ";
    oss << "instructions[" ;
    // oxm_basic_match match;
    uint32_t w = match.wildcards;
    oss << tab << "match {";
    if(!(w & OFPFW_IN_PORT))
        oss << " in_port(" << (int)match.OFB_IN_PORT << ")"; //uint16_t in_port;
    if(!match.OFB_ETH_DST.isUnspecified() && !(w & OFPFW_DL_DST))
        oss << " dl_dst(" << match.OFB_ETH_DST.str() << ")"; //inet::MacAddress dl_src;
    if(!match.OFB_ETH_SRC.isUnspecified() && !(w & OFPFW_DL_SRC))
        oss << " dl_src(" << match.OFB_ETH_SRC.str() << ")"; //inet::MacAddress dl_dst;
    if(!(w & OFPFW_DL_VLAN))
        oss << " dl_vlan(" << (int)match.OFB_VLAN_VID << ")"; //uint16_t dl_vlan;
    if(!(w & OFPFW_DL_VLAN_PCP))
        oss << " dl_vlan_pcp(" << (int)match.OFB_VLAN_PCP << ")"; //uint8_t dl_vlan_pcp;
    if(!(w & OFPFW_DL_TYPE))
        oss << " dl_type(" << (int)match.OFB_ETH_TYPE << ")"; //uint16_t dl_type;
    if(!(w & OFPFW_NW_PROTO))
        oss << " nw_proto(" << (int)match.OFB_IP_PROTO << ")"; //uint8_t nw_proto;
    if(!match.OFB_IPV4_SRC.isUnspecified() && !(w & OFPFW_NW_SRC_ALL))
        oss << " nw_src(" << match.OFB_IPV4_SRC.str(false) << ")"; //inet::Ipv4Address nw_src;
    if(!match.OFB_IPV4_DST.isUnspecified() && !(w & OFPFW_NW_DST_ALL))
        oss << " nw_dst(" << match.OFB_IPV4_DST.str(false) << ")"; //inet::Ipv4Address nw_dst;
    if(!(w & OFPFW_TP_SRC))
        oss << " tp_src(" << (int)match.OFB_TP_SRC << ")"; //uint16_t tp_src;
    if(!(w & OFPFW_TP_DST))
        oss << " tp_dst(" << (int)match.OFB_TP_DST << ")"; //uint16_t tp_dst;

    oss << " wildcards(" << match.wildcards << ")"; //uint32_t wildcards;
    oss << " } ";
    for (auto iter = instructions.begin(); iter < instructions.end(); iter++) {
        oss << "ofp_action_output( " << "port(" << iter->port << ") ) ";
    }
    oss << "] ";
    oss << " }";
    return oss.str();
}

} /* namespace openflow */
