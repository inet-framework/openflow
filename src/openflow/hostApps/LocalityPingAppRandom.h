

#include "inet/common/INETDefs.h"
#include "inet/applications/pingapp/PingApp.h"
#include "inet/networklayer/common/L3Address.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace inet;

namespace openflow{

/**
 * Generates ping requests and calculates the packet loss and round trip
 * parameters of the replies. Uses cTopology class to get all available destinations
 * and chooses random one
 *
 * See NED file for detailed description of operation.
 */
class LocalityPingAppRandom : public PingApp {
  protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual bool isEnabled();

    cTopology topo;
    std::string connectAddress;
    double localityRelation;
    std::string localId;
    std::map<std::string,std::vector<std::string> > groupToNodes;
};

} /*end namespace openflow*/
