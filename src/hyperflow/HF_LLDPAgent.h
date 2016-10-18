
#ifndef HFLLDPAGENT_H_
#define HFLLDPAGENT_H_

#include <omnetpp.h>
#include "LLDPAgent.h"
#include "AbstractControllerApp.h"
#include "LLDP_m.h"
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "LLDPMibGraph.h"
#include "OFP_Features_Reply_m.h"
#include "OFP_Packet_In_m.h"
#include "HyperFlowAgent.h"
#include "HF_ReFire_Wrapper.h"
#include "LLDP_Wrapper.h"


class HF_LLDPAgent:public LLDPAgent {


public:
    HF_LLDPAgent();
    ~HF_LLDPAgent();
    LLDPMibGraph * getMibGraph();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    void handlePacketIn(OFP_Packet_In * packet_in_msg);
    HyperFlowAgent * hfAgent;
    simsignal_t HyperFlowReFireSignalId;
};


#endif
