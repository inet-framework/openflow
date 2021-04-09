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

#include "openflow/openflow/switch/flowtable/OF_FlowTable.h"

#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

namespace openflow{

Define_Module(OF_FlowTable);

std::ostream& operator<<(std::ostream& os, const OF_FlowTableEntry& entry)
{
    os << entry.print();
    return os;
}

OF_FlowTable::OF_FlowTable() {
    for(auto&& entry : _entries) {
      delete entry;
    }
    _entries.clear();
}

OF_FlowTableEntry* OF_FlowTable::lookup(oxm_basic_match& match) {
    Enter_Method("lookup()");
    removeAgedEntriesIfNeeded();

    EV << "Looking through " << _entries.size() << " Flow Entries!" << '\n';

    for(auto iter =_entries.begin();iter != _entries.end();++iter){

        if ((*iter)->tryMatch(match)){
            (*iter)->setLastMatched(simTime());
            return (*iter);
        }
    }
    return nullptr;
}

OF_FlowTable::~OF_FlowTable() {
    clear();
}

void OF_FlowTable::initialize()
{
    handleParameterChange(nullptr);
    _tableIndex = this->getIndex();
    _nextAging = simtime_t::getMaxTime();

    WATCH(_nextAging);
    WATCH_PTRVECTOR(_entries);


    if(_agingInterval > 0){
        scheduleNextAging();
    }

    updateDisplayString();
}

void OF_FlowTable::handleParameterChange(const char* parname)
{
    if (!parname || !strcmp(parname, "agingInterval"))
    {
        _agingInterval = par("agingInterval").doubleValue();
    }
    if (!parname || !strcmp(parname, "maxFlowEntries"))
    {
        _maxEntries = par("maxFlowEntries");
    }
}

void OF_FlowTable::scheduleNextAging() {
    scheduleAt(simTime() + _agingInterval, new cMessage("AGING"));
}

void OF_FlowTable::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage() && !strcmp(msg->getName(), "AGING")) {
        //start aging
        removeAgedEntries();
    } else {
        throw cRuntimeError("This module doesn't process messages");
    }
    delete msg;
}

void OF_FlowTable::updateDisplayString() {
    if (!getEnvir()->isGUI())
            return;

    getDisplayString().setTagArg("t", 0, (to_string(getNumEntries()) + " flows").c_str());
}

void OF_FlowTable::sortEntries() {
    Enter_Method("sortEntries()");
    std::sort(_entries.rbegin(), _entries.rend());
}

bool OF_FlowTable::addEntry(OF_FlowTableEntry* entry) {
    Enter_Method("addEntry()");
    //abort if full
    if(_maxEntries != 0 && getNumEntries() >= _maxEntries)
        return false;

    //check if entry already exists.
    for(auto iter =_entries.begin();iter != _entries.end();++iter){
        //flow table entrys matches are equal
        if(entry == (*iter)) {
            return false;
        }
    }

    //insert entry and update timings.
    _entries.push_back(entry);
    const simtime_t now = simTime();
    entry->setCreationTime(now);
    entry->setLastMatched(now);
    removeAgedEntries();
    sortEntries();
    updateDisplayString();

    return true;
}

void OF_FlowTable::deleteMatchingEntries(oxm_basic_match& match) {
    Enter_Method("deleteMatchingEntries()");
    //check all entries
    for(auto iter =_entries.begin();iter != _entries.end(); ){
        OF_FlowTableEntry* entry = (*iter);
        //flow table entrys matches are equal
        if(entry->tryMatch(match, match.wildcards)) {
            _entries.erase(iter);
            delete entry;
        }else{
            ++iter;
        }
    }
    updateDisplayString();
}

vector<OF_FlowTableEntry*> OF_FlowTable::getEntrys(){
    return _entries;
}

void OF_FlowTable::handleFlowMod(OFP_Flow_Mod* flow_mod) {
    Enter_Method("handleFlowMod()");
    //check flow mod command
    switch(flow_mod->getCommand()){
    case ofp_flow_mod_command::OFPFC_ADD:
        addEntry(OF_FlowTableEntry::createEntryForOFVersion(flow_mod));
        break;
    //TODO Implement other flow mod commands
    case ofp_flow_mod_command::OFPFC_MODIFY:
    case ofp_flow_mod_command::OFPFC_MODIFY_STRICT:
    case ofp_flow_mod_command::OFPFC_DELETE:
        deleteMatchingEntries(flow_mod->getMatch());
    case ofp_flow_mod_command::OFPFC_DELETE_STRICT:
    default:
        break;
    }
}

void OF_FlowTable::clear() {
    Enter_Method("clear()");
    for(auto iter =_entries.begin();iter != _entries.end();++iter){
        OF_FlowTableEntry* entry = (*iter);
       delete entry;
    }
    _entries.clear();
    updateDisplayString();
}

void OF_FlowTable::removeAgedEntriesIfNeeded() {
    //return if no entries set or automatic aging turned off.
    if(_entries.empty() || _agingInterval > 0){
        return;
    }


    if (simTime() >= _nextAging)
    {
        removeAgedEntries();
    }
}

size_t OF_FlowTable::getNumEntries() {
    removeAgedEntriesIfNeeded();

    return _entries.size();
}

void OF_FlowTable::removeAgedEntries() {
    Enter_Method("removeAgedEntries()");
    bool updated = false;
    //get simtime.
    simtime_t now = simTime();

    //reset next aging.
    _nextAging = simtime_t::getMaxTime();

    //iterate over entries
    for(auto iter =_entries.begin();iter != _entries.end();++iter){
        OF_FlowTableEntry* entry = (*iter);
        simtime_t entryTimeout = entry->getTimeOut();
        if(now >= entryTimeout){
           _entries.erase(iter--);
           delete entry;
           updated = true;
        } else {
            //update next aging.
            if(_nextAging > entryTimeout){
                _nextAging = entryTimeout;
            }
        }
    }
    if(updated){
        sortEntries();
        updateDisplayString();
    }

    if(_agingInterval > 0){
        scheduleNextAging();
    }

}


std::string OF_FlowTable::exportToXML() {
    std::ostringstream oss;
    string tab = "    ";

    oss << "<flowTable index=\"" << _tableIndex << "\" >" << endl; // start flow table

    for(auto iter =_entries.begin();iter != _entries.end();++iter){
        oss << (*iter)->exportToXML();
    }

    oss << "</flowTable>" << endl;//end flow table
    return oss.str();
}

void OF_FlowTable::importFromXML(omnetpp::cXMLElement* xmlDoc) {
    //check if entry has correct index
    if(const char* value = xmlDoc->getAttribute("index")) {
        //check for our table index.
        if(atoi(value) != _tableIndex){
            //wrong table
            return;
        }
    } else {
        return;
    }

    //everything is allright so import.
    cXMLElementList xmlFlows = xmlDoc->getChildrenByTagName("flowEntry");
    for(size_t i=0; i<xmlFlows.size(); i++){
        if(OF_FlowTableEntry* entry = OF_FlowTableEntry::createEntryForOFVersion(xmlFlows[i])){
            addEntry(entry);
        }
    }

}

}
