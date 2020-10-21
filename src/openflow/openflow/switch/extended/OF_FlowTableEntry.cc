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

 #if OFP_VERSION_IN_USE == OFP_100
#include <openflow/openflow/switch/extended/OF100_FlowTableEntry.h>
#elif OFP_VERSION_IN_USE == OFP_135
#elif OFP_VERSION_IN_USE == OFP_141
#elif OFP_VERSION_IN_USE == OFP_151
#endif
#include <string>
#include <sstream>
using namespace std;
namespace openflow {


OF_FlowTableEntry::OF_FlowTableEntry(omnetpp::cXMLElement* xmlDoc) : OF_FlowTableEntry(){
    if(const char* value = xmlDoc->getAttribute("idleTimeout"))
        _idleTimeout = atoi(value);//idle timeout
    if(const char* value = xmlDoc->getAttribute("hardTimeout"))
        _hardTimeout = atoi(value);//hard timeout
}

OF_FlowTableEntry::OF_FlowTableEntry(OFP_Flow_Mod* flow_mod) : OF_FlowTableEntry(){
    _hardTimeout = flow_mod->getHard_timeout();
    _idleTimeout = flow_mod->getIdle_timeout();
}

OF_FlowTableEntry::OF_FlowTableEntry() {
    simtime_t now = simTime();
    _creationTime = now;
    _lastMatched = now;
}

OF_FlowTableEntry* OF_FlowTableEntry::createEntryForOFVersion(OFP_Flow_Mod* flow_mod) {
#if OFP_VERSION_IN_USE == OFP_100
    return new OF100_FlowTableEntry(flow_mod);
#elif OFP_VERSION_IN_USE == OFP_135
    return NULL;
#elif OFP_VERSION_IN_USE == OFP_141
    return NULL;
#elif OFP_VERSION_IN_USE == OFP_151
    return NULL;
#endif
}

OF_FlowTableEntry* OF_FlowTableEntry::createEntryForOFVersion() {
#if OFP_VERSION_IN_USE == OFP_100
    return new OF100_FlowTableEntry();
#elif OFP_VERSION_IN_USE == OFP_135
    return nullptr;
#elif OFP_VERSION_IN_USE == OFP_141
    return nullptr;
#elif OFP_VERSION_IN_USE == OFP_151
    return nullptr;
#endif
}

OF_FlowTableEntry* OF_FlowTableEntry::createEntryForOFVersion(omnetpp::cXMLElement* xmlDoc) {
#if OFP_VERSION_IN_USE == OFP_100
    return new OF100_FlowTableEntry(xmlDoc);
#elif OFP_VERSION_IN_USE == OFP_135
    return nullptr;
#elif OFP_VERSION_IN_USE == OFP_141
    return nullptr;
#elif OFP_VERSION_IN_USE == OFP_151
    return nullptr;
#endif
}

simtime_t OF_FlowTableEntry::getTimeOut() {
    simtime_t timeout = simtime_t::getMaxTime();//never timeout.

    //check if hard timeout or idle timeOut are earlier.
    if(_idleTimeout > 0) {
        simtime_t idleTimeout =  _lastMatched + _idleTimeout;
        if(timeout > idleTimeout) {
            timeout = idleTimeout;
        }
    }
    if(_hardTimeout > 0) {
        simtime_t hardTimeout =  _creationTime + _hardTimeout;
        if(timeout > hardTimeout) {
            timeout = hardTimeout;
        }
    }
    return timeout;
}


std::string OF_FlowTableEntry::print() const {
    ostringstream oss;
    oss << "OF_FlowTableEntry{ ";
    oss << "creationTime(" << _creationTime.str() << ") ";
    oss << "lastMatched(" << _lastMatched.str() << ") ";
    oss << "hardTimeout(" << _hardTimeout << ") ";
    oss << "idleTimeout(" << _idleTimeout << ") ";
    oss << " }";
    return oss.str();
}

std::string OF_FlowTableEntry::exportToXML() {
    std::ostringstream oss;
    string tab = "    ";
    //begin flow entry
    oss << "<flowEntry";
    oss << " hardTimeout=\"" << _hardTimeout << "\"";
    oss << " idleTimeout=\"" << _idleTimeout << "\"";
    oss << " />" << endl;//end flow entry
    return oss.str();
}
} /* namespace openflow */
