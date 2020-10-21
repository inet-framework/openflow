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

#include <openflow/openflow/switch/extended/OF100_FlowTableEntry.h>
#include "inet/linklayer/common/MACAddress.h"
#include "inet/networklayer/contract/ipv4/IPv4Address.h"
#include <string>
#include <sstream>

using namespace std;
using namespace inet;

namespace openflow {

OF100_FlowTableEntry::OF100_FlowTableEntry() {
    //init counters
}

OF100_FlowTableEntry::OF100_FlowTableEntry(OFP_Flow_Mod* flow_mod) : OF_FlowTableEntry(flow_mod){
    _cookie = flow_mod->getCookie();
    _priority = flow_mod->getPriority();
    _flags = flow_mod->getFlags();
    _match = flow_mod->getMatch();
    for (size_t i = 0 ; i < flow_mod->getActionsArraySize(); i++){
        _instructions.push_back(flow_mod->getActions(i));
    }
}

OF100_FlowTableEntry::OF100_FlowTableEntry(omnetpp::cXMLElement* xmlDoc) : OF_FlowTableEntry(xmlDoc){
    //get attributes
    if(const char* value = xmlDoc->getAttribute("cookie"))
        _cookie = atoi(value);//cookie
    if(const char* value = xmlDoc->getAttribute("flags"))
        _flags = atoi(value);//flags
    if(const char* value = xmlDoc->getAttribute("priority"))
        _priority = atoi(value);//priority

    if(cXMLElement* xmlMatch = xmlDoc->getFirstChildWithTag("match")){
        if(const char* value = xmlMatch->getAttribute("in_port"))
            _match.in_port = atoi(value);
        if(const char* value = xmlMatch->getAttribute("dl_src"))
            _match.dl_src = MACAddress(value);
        if(const char* value = xmlMatch->getAttribute("dl_dst"))
            _match.dl_dst = MACAddress(value);
        if(const char* value = xmlMatch->getAttribute("dl_vlan"))
            _match.dl_vlan = atoi(value);
        if(const char* value = xmlMatch->getAttribute("dl_vlan_pcp"))
            _match.dl_vlan_pcp = atoi(value);
        if(const char* value = xmlMatch->getAttribute("dl_type"))
            _match.dl_type = atoi(value);
        if(const char* value = xmlMatch->getAttribute("nw_proto"))
            _match.nw_proto = atoi(value);
        if(const char* value = xmlMatch->getAttribute("nw_src"))
            _match.nw_src = IPv4Address(value);
        if(const char* value = xmlMatch->getAttribute("nw_dst"))
            _match.nw_dst = IPv4Address(value);
        if(const char* value = xmlMatch->getAttribute("tp_src"))
            _match.tp_src = atoi(value);
        if(const char* value = xmlMatch->getAttribute("tp_dst"))
            _match.tp_dst = atoi(value);
        if(const char* value = xmlMatch->getAttribute("wildcards"))
            _match.wildcards = atoi(value);
    }

    //get instructions
    cXMLElement* xmlInstructions = xmlDoc->getFirstChildWithTag("instructions");
    cXMLElementList xmlInstructionList = xmlInstructions->getChildrenByTagName("action_output");
    for (size_t i=0; i<xmlInstructionList.size(); i++){
        ofp_action_output action;
        action.port = atoi(xmlInstructionList[i]->getAttribute("port"));
        _instructions.push_back(action);
    }

}

OF100_FlowTableEntry::~OF100_FlowTableEntry() {
    _instructions.clear();
}

bool OF100_FlowTableEntry::tryMatch(oxm_basic_match& other) {
    return tryMatch(other, _match.wildcards);
}

bool OF100_FlowTableEntry::tryMatch(oxm_basic_match& other, uint32_t wildcards) {
    //debuggable
//    bool port = ((wildcards & OFPFW_IN_PORT) || _match.in_port == other.in_port) ;
//    bool dl_type = ((wildcards & OFPFW_DL_TYPE) || _match.dl_type == other.dl_type ) ;
//    bool dl_src = ((wildcards & OFPFW_DL_SRC) || !_match.dl_src.compareTo(other.dl_src)) ;
//    bool dl_dst = ((wildcards & OFPFW_DL_DST) || !_match.dl_dst.compareTo(other.dl_dst)) ;
//    bool dl_vlan = ((wildcards & OFPFW_DL_VLAN) || _match.dl_vlan == other.dl_vlan ) ;
//    bool dl_vlan_pcb = ((wildcards & OFPFW_DL_VLAN_PCP) || _match.dl_vlan_pcp == other.dl_vlan_pcp ) ;
//    bool nw_proto = ((wildcards & OFPFW_NW_PROTO) || _match.nw_proto == other.nw_proto ) ;
//    bool nw_src = ((wildcards & OFPFW_NW_SRC_ALL) || _match.nw_src.equals(other.nw_src) ) ;
//    bool nw_dst = ((wildcards & OFPFW_NW_DST_ALL) || _match.nw_dst.equals(other.nw_dst) ) ;
//    bool tp_src = ((wildcards & OFPFW_TP_SRC) || _match.tp_src == other.tp_src ) ;
//    bool tp_dst = ((wildcards & OFPFW_TP_DST) || _match.tp_src == other.tp_src ) ;
    return ((wildcards & OFPFW_IN_PORT) || _match.in_port == other.in_port) &&
        ((wildcards & OFPFW_DL_TYPE) || _match.dl_type == other.dl_type ) &&
        ((wildcards & OFPFW_DL_SRC) || !_match.dl_src.compareTo(other.dl_src)) &&
        ((wildcards & OFPFW_DL_DST) || !_match.dl_dst.compareTo(other.dl_dst)) &&
        ((wildcards & OFPFW_DL_VLAN) || _match.dl_vlan == other.dl_vlan ) &&
        ((wildcards & OFPFW_DL_VLAN_PCP) || _match.dl_vlan_pcp == other.dl_vlan_pcp ) &&
        ((wildcards & OFPFW_NW_PROTO) || _match.nw_proto == other.nw_proto ) &&
        ((wildcards & OFPFW_NW_SRC_ALL) || _match.nw_src.equals(other.nw_src) ) &&
        ((wildcards & OFPFW_NW_DST_ALL) || _match.nw_dst.equals(other.nw_dst) ) &&
        ((wildcards & OFPFW_TP_SRC) || _match.tp_src == other.tp_src ) &&
        ((wildcards & OFPFW_TP_DST) || _match.tp_src == other.tp_src );
}

std::string OF100_FlowTableEntry::exportToXML() {
    std::ostringstream oss;
    string tab = "    ";
    oss << "<flowEntry";
    oss << " hardTimeout=\"" << _hardTimeout << "\"";
    oss << " idleTimeout=\"" << _idleTimeout << "\"";
    oss << " cookie=\"" << _cookie << "\"";
    oss << " priority=\"" << _priority << "\"";
    oss << " flags=\"" << _flags << "\"";
    oss << " >" << endl;//end flow entry


    // oxm_basic_match match;
    uint32_t w = _match.wildcards;
    oss << tab << "<match ";
    if(!(w & OFPFW_IN_PORT))
        oss << " in_port=\"" << (int)_match.in_port << "\""; //uint16_t in_port;
    if(!_match.dl_dst.isUnspecified() && !(w & OFPFW_DL_DST))
        oss << " dl_dst=\"" << _match.dl_dst.str() << "\""; //inet::MACAddress dl_src;
    if(!_match.dl_src.isUnspecified() && !(w & OFPFW_DL_SRC))
        oss << " dl_src=\"" << _match.dl_src.str() << "\""; //inet::MACAddress dl_dst;
    if(!(w & OFPFW_DL_VLAN))
        oss << " dl_vlan=\"" << (int)_match.dl_vlan << "\""; //uint16_t dl_vlan;
    if(!(w & OFPFW_DL_VLAN_PCP))
        oss << " dl_vlan_pcp=\"" << (int)_match.dl_vlan_pcp << "\""; //uint8_t dl_vlan_pcp;
    if(!(w & OFPFW_DL_TYPE))
        oss << " dl_type=\"" << (int)_match.dl_type << "\""; //uint16_t dl_type;
    if(!(w & OFPFW_NW_PROTO))
        oss << " nw_proto=\"" << (int)_match.nw_proto << "\""; //uint8_t nw_proto;
    if(!_match.nw_src.isUnspecified() && !(w & OFPFW_NW_SRC_ALL))
        oss << " nw_src=\"" << _match.nw_src.str(false) << "\""; //inet::IPv4Address nw_src;
    if(!_match.nw_dst.isUnspecified() && !(w & OFPFW_NW_DST_ALL))
        oss << " nw_dst=\"" << _match.nw_dst.str(false) << "\""; //inet::IPv4Address nw_dst;
    if(!(w & OFPFW_TP_SRC))
        oss << " tp_src=\"" << (int)_match.tp_src << "\""; //uint16_t tp_src;
    if(!(w & OFPFW_TP_DST))
        oss << " tp_dst=\"" << (int)_match.tp_dst << "\""; //uint16_t tp_dst;

    oss << " wildcards=\"" << _match.wildcards << "\""; //uint32_t wildcards;
    oss << " />" << endl;

    // std::vector<ofp_action_output> instructions;
    if(!_instructions.empty()){
        oss << tab << "<instructions>" << endl;
        for (uint32_t i=0;i<_instructions.size();i++){
            int port = _instructions[i].port;
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
    oss << "cookie(" << _cookie << ") ";
    oss << "priority(" << _priority << ") ";
    oss << "flags(" << _flags << ") ";
    oss << "instructions[" ;
    // oxm_basic_match match;
    uint32_t w = _match.wildcards;
    oss << tab << "match {";
    if(!(w & OFPFW_IN_PORT))
        oss << " in_port(" << (int)_match.in_port << ")"; //uint16_t in_port;
    if(!_match.dl_dst.isUnspecified() && !(w & OFPFW_DL_DST))
        oss << " dl_dst(" << _match.dl_dst.str() << ")"; //inet::MACAddress dl_src;
    if(!_match.dl_src.isUnspecified() && !(w & OFPFW_DL_SRC))
        oss << " dl_src(" << _match.dl_src.str() << ")"; //inet::MACAddress dl_dst;
    if(!(w & OFPFW_DL_VLAN))
        oss << " dl_vlan(" << (int)_match.dl_vlan << ")"; //uint16_t dl_vlan;
    if(!(w & OFPFW_DL_VLAN_PCP))
        oss << " dl_vlan_pcp(" << (int)_match.dl_vlan_pcp << ")"; //uint8_t dl_vlan_pcp;
    if(!(w & OFPFW_DL_TYPE))
        oss << " dl_type(" << (int)_match.dl_type << ")"; //uint16_t dl_type;
    if(!(w & OFPFW_NW_PROTO))
        oss << " nw_proto(" << (int)_match.nw_proto << ")"; //uint8_t nw_proto;
    if(!_match.nw_src.isUnspecified() && !(w & OFPFW_NW_SRC_ALL))
        oss << " nw_src(" << _match.nw_src.str(false) << ")"; //inet::IPv4Address nw_src;
    if(!_match.nw_dst.isUnspecified() && !(w & OFPFW_NW_DST_ALL))
        oss << " nw_dst(" << _match.nw_dst.str(false) << ")"; //inet::IPv4Address nw_dst;
    if(!(w & OFPFW_TP_SRC))
        oss << " tp_src(" << (int)_match.tp_src << ")"; //uint16_t tp_src;
    if(!(w & OFPFW_TP_DST))
        oss << " tp_dst(" << (int)_match.tp_dst << ")"; //uint16_t tp_dst;

    oss << " wildcards(" << _match.wildcards << ")"; //uint32_t wildcards;
    oss << " } ";
    for (auto iter = _instructions.begin(); iter < _instructions.end(); iter++) {
        oss << "ofp_action_output( " << "port(" << iter->port << ") ) ";
    }
    oss << "] ";
    oss << OF_FlowTableEntry::print();
    oss << " }";
    return oss.str();
}

} /* namespace openflow */
