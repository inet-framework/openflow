
#ifndef LLDPAGENTFORWARDING_H_
#define LLDPAGENTFORWARDING_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "openflow/controllerApps/LLDPAgent.h"
#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/controllerApps/LLDPMib.h"
#include "openflow/messages/OFP_Packet_In_m.h"
#include "inet/networklayer/arp/ipv4/ARPPacket_m.h"

namespace openflow{

struct LLDPPathSegment{
    std::string chassisId;
    int outport;
};

class LLDPForwarding:public AbstractControllerApp {


public:
    LLDPForwarding();
    ~LLDPForwarding();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg);
    virtual void computePath(std::string srcId, std::string dstId, std::list<LLDPPathSegment> &list);


    LLDPAgent * lldpAgent;
    long flooded;
    long forwarded;
    long dropped;
    bool dropIfNoRouteFound;
    bool ignoreArpRequests;
    bool printMibGraph;
    long version;
    long versionHit;
    long versionMiss;
    long cacheHit;
    long cacheMiss;

    int idleTimeout;
    int hardTimeout;

    std::map<std::pair<std::string,std::string>, std::list<LLDPPathSegment> > routeCache;


};

} /*end namespace openflow*/

#endif
