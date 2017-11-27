
#ifndef KNLLDPAGENT_H_
#define KNLLDPAGENT_H_

#include <omnetpp.h>
#include "LLDPAgent.h"
#include "AbstractControllerApp.h"
#include "LLDP_m.h"
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "LLDPMibGraph.h"
#include "OFP_Features_Reply_m.h"
#include "OFP_Packet_In_m.h"
#include "KandooAgent.h"
#include "LLDP_Wrapper.h"


class KN_LLDPAgent:public LLDPAgent {


public:
    KN_LLDPAgent();
    ~KN_LLDPAgent();
    LLDPMibGraph * getMibGraph();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    void handlePacketIn(OFP_Packet_In * packet_in_msg);
    KandooAgent * kandooAgent;
    simsignal_t kandooEventSignalId;
    std::string appName;
};


#endif
