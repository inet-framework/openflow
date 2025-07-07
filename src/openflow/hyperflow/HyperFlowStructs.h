#ifndef HYPERFLOWSTRUCTS_H_
#define HYPERFLOWSTRUCTS_H_

#include "openflow/openflow/controller/Switch_Info.h"

namespace openflow {

struct ControlChannelEntry {
    std::list<Switch_Info *> switches;
    std::string controllerId;
    SimTime time;

    // getters for descriptor:
    const char *getControllerId() const { return controllerId.c_str(); }
    simtime_t getTime() const { return time; }
    size_t getSwitchesArraySize() { return switches.size(); }
    const Switch_Info *getSwitches(int i) const {
        if (i < 0 || static_cast<size_t>(i) >= switches.size())
            throw std::out_of_range("Cannot return field, index out of range.");
        auto it = switches.begin();
        std::advance(it, i);
        return *it;
    }

};

struct DataChannelEntry {
    std::string srcController;
    std::string trgSwitch;
    int eventId;
    omnetpp::cObject *payload;

    // getters for descriptor:
    const char *getSrcController() const { return srcController.c_str(); }
    const char *getTrgSwitch() const { return trgSwitch.c_str(); }
    int getEventId() const { return eventId; }
    const omnetpp::cObject *getPayload() const { return payload; }
};

} /*end namespace openflow*/

#endif /* OF_CONTROLLER_H_ */

