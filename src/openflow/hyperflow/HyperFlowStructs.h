
#ifndef HYPERFLOWSTRUCTS_H_
#define HYPERFLOWSTRUCTS_H_

#include "Switch_Info.h"

struct ControlChannelEntry{
    std::list<Switch_Info *> switches;
    std::string controllerId;
    SimTime time;
};

struct DataChannelEntry{
    std::string srcController;
    std::string trgSwitch;
    int eventId;
    cObject * payload;
};



#endif /* OF_CONTROLLER_H_ */
