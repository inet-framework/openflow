
#ifndef KANDOOSTRUCTS_H_
#define KANDOOSTRUCTS_H_

#include "omnetpp.h"
using namespace omnetpp;

namespace openflow{

struct KandooEntry{
    std::string srcController;
    std::string trgController;
    std::string trgApp;
    std::string srcApp;
    std::string trgSwitch;
    std::string srcSwitch;
    omnetpp::cObject * payload = nullptr;
    int type = -1; //0 inform, 1 request, 2 reply
};

} /*end namespace openflow*/

#endif /* OF_CONTROLLER_H_ */
