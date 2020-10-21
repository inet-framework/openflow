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


#ifndef OPENFLOW_OPENFLOW_SWITCH_OF_FLOWTABLEENTRY_H_
#define OPENFLOW_OPENFLOW_SWITCH_OF_FLOWTABLEENTRY_H_

#include <openflow/openflow/protocol/OpenFlow.h>
#include <openflow/messages/OFP_Flow_Mod_m.h>
#include <omnetpp.h>

namespace openflow {

/**
 * Abstract Flow Table Entry providing the basic, protocol independent functionality of flow table entries.
 * And interface functions for protocol specific behavior.
 * @author Timo Haeckel, for HAW Hamburg
 */
class OF_FlowTableEntry {

public:
    //constructor, forces subclasses to implement them aswell.
    OF_FlowTableEntry(omnetpp::cXMLElement* xmlDoc);
    OF_FlowTableEntry(OFP_Flow_Mod* flow_mod);
    OF_FlowTableEntry();
    virtual ~OF_FlowTableEntry(){}

    /**
     * Creates an OF_FlowTableEntry for the currently used Openflow protocol version.
     * @return              A new Entry.
     */
    static OF_FlowTableEntry* createEntryForOFVersion();

    /**
     * Creates an OF_FlowTableEntry for the currently used Openflow protocol version.
     * According to an incoming flow mod message, setting all containing parameters.
     * @param flow_mod      The Flow mod message
     * @return              A new Entry.
     */
    static OF_FlowTableEntry* createEntryForOFVersion(OFP_Flow_Mod* flow_mod);
    /**
     * Creates an OF_FlowTableEntry for the currently used Openflow protocol version.
     * According to an xmldocument containing a falid <flowTableEntry> tag with all specified paramenters.
     * @param xmlDoc        The xmlElement of the <flowTableEntry>.
     * @return              A new Entry.
     */
    static OF_FlowTableEntry* createEntryForOFVersion(omnetpp::cXMLElement* xmlDoc);

//interface methods.
    /**
     * Smaller (<) comparison operator needs to be overwritten to allow sorting FlowTableEntries.
     * @param l the left hand side
     * @param r the write hand side
     * @return true if l<r
     */
    friend bool operator<(const OF_FlowTableEntry& l, const OF_FlowTableEntry& r){
        if(l.lastMatched < r.lastMatched){
            return true;
        } else if (l.lastMatched > r.lastMatched){
            return false;
        } else {
            if(l.creationTime < r.creationTime){
                return true;
            } else if (l.creationTime > r.creationTime){
                return false;
            } else{
                return false;
            }
        }
        return false;
    }

    /**
     * Export this flow entry as an XML formatted String.
     * @return XML formatted string value.
     */
    virtual std::string exportToXML();

    /**
     * Print this as string representation.
     * @return the print string
     */
    virtual std::string print() const;

    /**
     * TODO maybe introduce an abstract type that is not protocol dependent.
     * Checks if the flow matches the rules in this entry.
     * @param other The incoming flow.
     * @return true if the rules match.
     */
    virtual bool tryMatch(oxm_basic_match& other) = 0;

    /**
     * TODO maybe introduce an abstract type that is not protocol dependent.
     * Checks if the flow matches the rules in this entry.
     * @param other The incoming flow.
     * @param wildcards The wildcards for matching.
     * @return true if the rules match.
     */
    virtual bool tryMatch(oxm_basic_match& other, uint32_t wildcards) = 0;

    /**
     * TODO maybe introduce an abstract type that is not protocol dependent.
     * Get the instructions of this entry.
     * @return the instruction vector
     */
    virtual const std::vector<ofp_action_output>& getInstructions() const = 0;

    /**
     * Calculate when this entry expires according to hard or idle timeout.
     * @return The time this entry expires.
     */
    virtual simtime_t getTimeOut();

//getter and setter
    const simtime_t& getCreationTime() const {
        return creationTime;
    }
    void setCreationTime(const simtime_t& creationTime) {
        this->creationTime = creationTime;
    }
    double getHardTimeout() const {
        return hardTimeout;
    }
    void setHardTimeout(double hardTimeout) {
        this->hardTimeout = hardTimeout;
    }
    double getIdleTimeout() const {
        return idleTimeout;
    }
    void setIdleTimeout(double idleTimeout) {
        this->idleTimeout = idleTimeout;
    }
    const simtime_t& getLastMatched() const {
        return lastMatched;
    }
    void setLastMatched(const simtime_t& lastMatched) {
        this->lastMatched = lastMatched;
    }

protected:
    /**
     * Simulation timestamp on creation of this entry.
     */
    simtime_t creationTime;
    /**
     * Simulation timestamp on the last match for this entry
     */
    simtime_t lastMatched;

    /**
     * in seconds
     */
    double hardTimeout;
    /**
     * in seconds
     */
    double idleTimeout;
};

} /* namespace openflow */

#endif /* OPENFLOW_OPENFLOW_SWITCH_OF_FLOWTABLEENTRY_H_ */
