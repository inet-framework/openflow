
#ifndef FLOW_TABLE_H_
#define FLOW_TABLE_H_

#include <vector>
#include "openflow/openflow/protocol/OpenFlow.h"
#include "openflow/openflow/switch/Flow_Table_Entry.h"

using namespace __gnu_cxx;


namespace openflow{

class Flow_Table {
public:
    Flow_Table();
    virtual ~Flow_Table();
    void addEntry(Flow_Table_Entry entry);
    Flow_Table_Entry * lookup(oxm_basic_match &match);
    void removeExpiredEntries();
    /**
     * @brief For lifecycle: clears all entries from the table.
     */
    virtual void clear();


private:
    std::list<Flow_Table_Entry> entryList;
};



} /*end namespace openflow*/

#endif /* FLOW_TABLE_H_ */
