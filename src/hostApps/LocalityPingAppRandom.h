

#include "INETDefs.h"
#include "PingApp.h"
#include "IPvXAddress.h"
#include <iostream>
#include <fstream>
#include <vector>

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
    const char *connectAddress;
    double localityRelation;
    std::string localId;
    std::map<std::string,std::vector<std::string> > groupToNodes;
};


