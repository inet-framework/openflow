#ifndef __OPENFLOW_KANDOOSTRUCTS_H
#define __OPENFLOW_KANDOOSTRUCTS_H

#include "omnetpp.h"
using namespace omnetpp;

namespace openflow {

struct KandooEntry {
    std::string srcController;
    std::string trgController;
    std::string trgApp;
    std::string srcApp;
    std::string trgSwitch;
    std::string srcSwitch;
    omnetpp::cObject *payload = nullptr;
    int type = -1; //0 inform, 1 request, 2 reply

    // getters for descriptor:
    const char *getSrcController() const { return srcController.c_str(); }
    const char *getTrgController() const { return trgController.c_str(); }
    const char *getTrgApp() const { return trgApp.c_str(); }
    const char *getSrcApp() const { return srcApp.c_str(); }
    const char *getTrgSwitch() const { return trgSwitch.c_str(); }
    const char *getSrcSwitch() const { return srcSwitch.c_str(); }
    const omnetpp::cObject *getPayload() const { return payload; }
    int getType() const { return type; }
};

} /*end namespace openflow*/

#endif

