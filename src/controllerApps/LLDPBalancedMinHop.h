
#ifndef LLDPBALANCEDMINHOP_H_
#define LLDPBALANCEDMINHOP_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "LLDPAgent.h"
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "LLDPMib.h"
#include "OFP_Packet_In_m.h"
#include "ARPPacket_m.h"

struct LLDPPathSegment{
    std::string chassisId;
    int outport;
};

class LLDPBalancedMinHop:public AbstractControllerApp {


public:
    LLDPBalancedMinHop();
    ~LLDPBalancedMinHop();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg);
    virtual std::list<LLDPPathSegment> computeBalancedMinHopPath(std::string srcId, std::string dstId);

    LLDPAgent * lldpAgent;
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


#endif
