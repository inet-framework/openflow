
#ifndef LLDPAGENT_H_
#define LLDPAGENT_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "LLDP_m.h"
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "LLDPMibGraph.h"
#include "OFP_Features_Reply_m.h"
#include "OFP_Packet_In_m.h"


class LLDPAgent:public AbstractControllerApp {


public:
    LLDPAgent();
    ~LLDPAgent();
    LLDPMibGraph * getMibGraph();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    virtual void handleMessage(cMessage *msg);
    void triggerFlowMod(Switch_Info * swInfo);
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg);
    void sendLLDP();
    double pollInterval;
    double timeOut;
    LLDPMibGraph mibGraph;
    bool printMibGraph;
    int idleTimeout;
    int hardTimeout;
};


#endif
