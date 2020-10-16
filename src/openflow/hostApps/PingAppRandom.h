
#include "inet/common/INETDefs.h"
#include "inet/applications/pingapp/PingApp.h"
#include "inet/networklayer/common/L3Address.h"

namespace openflow{

/**
 * Generates ping requests and calculates the packet loss and round trip
 * parameters of the replies. Uses cTopology class to get all available destinations
 * and chooses random one
 *
 * See NED file for detailed description of operation.
 */
class PingAppRandom : public inet::PingApp {
  protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
    virtual bool isEnabled();

    cTopology topo;
    std::string connectAddress;

    //stats
    simsignal_t pingPacketHash;
};

} /*end namespace openflow*/


