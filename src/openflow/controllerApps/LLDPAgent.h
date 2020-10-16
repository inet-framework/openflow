
#ifndef LLDPAGENT_H_
#define LLDPAGENT_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "openflow/messages/LLDP_m.h"
#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/controllerApps/LLDPMibGraph.h"
#include "openflow/messages/OFP_Features_Reply_m.h"
#include "openflow/messages/OFP_Packet_In_m.h"

namespace openflow{

class LLDPAgent:public AbstractControllerApp {


public:
    LLDPAgent();
    ~LLDPAgent();
    LLDPMibGraph * getMibGraph();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
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

} /*end namespace openflow*/

#endif
