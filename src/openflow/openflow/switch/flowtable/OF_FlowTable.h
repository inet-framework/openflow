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


#ifndef __OPENFLOW_OF_FLOWTABLE_H_
#define __OPENFLOW_OF_FLOWTABLE_H_

#include <omnetpp.h>
#include <vector>
#include <string>

#include "openflow/openflow/switch/flowtable/OF_FlowTableEntry.h"

using namespace omnetpp;

namespace openflow {

/**
 * Flow Table Module for Openflow Switch.
 * @author Timo Haeckel, for HAW Hamburg
 */
class OF_FlowTable: public cSimpleModule {

public:
    friend std::ostream& operator<<(std::ostream& os, const OF_FlowTableEntry& entry);

    /**
     * Export this flow Table as an XML fromatted String.
     * @return XML formatted string value.
     */
    std::string exportToXML();

    /**
     * Import flow table entries from XML Document..
     * @param xmlDoc flow table xml with root of <flowTable index="x"> elements.
     */
    void importFromXML(omnetpp::cXMLElement* xmlDoc);

    /**
     * Inserts the entry into the table if it does not already exist.
     * @param entry The entry to insert.
     * @return true if entry inserted.
     */
    bool addEntry(OF_FlowTableEntry* entry);

    /**
     * Handles the openflow flow mod message and updated the flow table accordingly
     * @param flow_mod the openflow flow modification message.
     */
    void handleFlowMod(OFP_Flow_Mod* flow_mod);

    /**
     * Deletes all entries matching the match.
     * @param match the match description.
     */
    void deleteMatchingEntries(oxm_basic_match& match);

    /**
     * TODO maybe use abstract flow description type that is not protocol dependent.
     * Check if an entry in this table matches.
     * @param match flow to lookup
     * @return the matching flow entry.
     */
    OF_FlowTableEntry* lookup(oxm_basic_match &match);

    /**
     * @return returns a vector containing all saved FlowTableEntrys
     */
    std::vector<OF_FlowTableEntry*> getEntrys();

    /**
     * @brief For lifecycle: clears all entries from the table.
     */
    virtual void clear();

    /**
     * @brief Remove entries that were not updated during agingTime if necessary
     */
    void removeAgedEntriesIfNeeded();


protected:
    virtual void initialize() override;
    virtual void handleParameterChange(const char* parname) override;

    /**
     * Schedules a self message to start aging process
     */
    void scheduleNextAging();

    /**
     * @brief Table does not receive messages except scheduled aging self messages,
     *        throws cRuntimeError when handleMessage when any other received.
     * @param msg unchecked.
     */
    virtual void handleMessage(cMessage *msg) override;

    /**
     * @brief updates the displaystring of talkers and listeners
     */
    void updateDisplayString();

    /**
     * @brief get the number of flow table entries
     *
     * @return number of flow table entries
     */
    size_t getNumEntries();

    /**
     * @brief Remove entries that were not updated during agingTime.
     */
    void removeAgedEntries();

    /**
     * Sorts the entries in descending order comparing the entries using the <operator.
     * Should be called after updating the vector.
     */
    void sortEntries();

public:
    /**
     *  @brief Constructor
     */
    OF_FlowTable();

    /**
     *  @brief Destructor
     */
    virtual ~OF_FlowTable() override;

private:
    /**
     * Cached Table Index in the Switch.
     */
    int _tableIndex;

    /**
     * Flow Table entries
     */
    std::vector<OF_FlowTableEntry*> _entries;

    /**
     * Maximum number of Flow Table entries.
     */
    unsigned int _maxEntries;

    /**
     * Time when next entry is aging.
     */
    simtime_t _nextAging;

    /**
     * Cached aging check interval.
     */
    double _agingInterval;
};

} /* namespace openflow */

#endif
