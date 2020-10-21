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

#ifndef OPENFLOW_OPENFLOW_SWITCH_OF100_FLOWTABLEENTRY_H_
#define OPENFLOW_OPENFLOW_SWITCH_OF100_FLOWTABLEENTRY_H_

#include <openflow/openflow/switch/extended/OF_FlowTableEntry.h>

namespace openflow {

/**
 * Implements the behaviour of an OF_FlowTableEntry in Openflow Version 1.0.0
 * @author Timo Haeckel, for HAW Hamburg
 */
class OF100_FlowTableEntry: public OF_FlowTableEntry {
public:
    OF100_FlowTableEntry(omnetpp::cXMLElement* xmlDoc);
    OF100_FlowTableEntry(OFP_Flow_Mod* flow_mod);
    OF100_FlowTableEntry();
    virtual ~OF100_FlowTableEntry();

    /**
     * Allows to sort flow table entries.
     * first sorts on entry priority if equal sorts on lastMatched if equal sorts on creationTime.
     * @param l the left hand side of the < operation
     * @param r the right hand side of the < operation
     * @return true if l < r
     */
    friend bool operator<(const OF100_FlowTableEntry& l, const OF100_FlowTableEntry& r)
    {
        if(l._priority < r._priority){
            return true;
        } else if (l._priority > r._priority){
            return false;
        } else { // l._priority = r._priority
            if(l._lastMatched < r._lastMatched){
                return true;
            } else if (l._lastMatched > r._lastMatched){
                return false;
            } else {
                if(l._creationTime < r._creationTime){
                    return true;
                } else if (l._creationTime > r._creationTime){
                    return false;
                } else{
                    return false;
                }
            }
        }
        return false;
    }

    //interface methods.
    /**
     * Export this flow entry as an XML formatted String.
     * @return XML formatted string value.
     */
    virtual std::string exportToXML() override;

    /**
     * Print this as string representation.
     * @return the print string
     */
    virtual std::string print() const override;

    /**
     * Checks if the flow matches the rules in this entry.
     * @param other The incoming flow.
     * @return true if the rules match.
     */
    virtual bool tryMatch(oxm_basic_match& other) override;

    /**
     * Checks if the flow matches the rules in this entry.
     * @param other The incoming flow.
     * @param wildcards The wildcards for matching.
     * @return true if the rules match.
     */
    virtual bool tryMatch(oxm_basic_match& other, uint32_t wildcards) override;

    uint64_t getCookie() const {
        return _cookie;
    }
    void setCookie(uint64_t cookie) {
        _cookie = cookie;
    }
    const std::vector<ofp_action_output>& getInstructions() const {
        return _instructions;
    }
    void setInstructions(const std::vector<ofp_action_output>& instructions) {
        _instructions = instructions;
    }
    const oxm_basic_match& getMatch() const {
        return _match;
    }
    void setMatch(const oxm_basic_match& match) {
        _match = match;
    }
    int getPriority() const {
        return _priority;
    }
    void setPriority(int priority) {
        _priority = priority;
    }
    uint32_t getFlags() const {
        return _flags;
    }
    void setFlags(uint32_t flags) {
        this->_flags = flags;
    }

protected:
    uint64_t _cookie;
    int _priority;
    uint32_t _flags;
    oxm_basic_match _match;
    std::vector<ofp_action_output> _instructions;
    //TODO counters?

};

} /* namespace openflow */

#endif /* OPENFLOW_OPENFLOW_SWITCH_OF100_FLOWTABLEENTRY_H_ */
