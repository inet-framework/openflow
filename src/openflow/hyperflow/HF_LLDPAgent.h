
#ifndef HFLLDPAGENT_H_
#define HFLLDPAGENT_H_

#include <omnetpp.h>
#include "openflow/controllerApps/LLDPAgent.h"
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "openflow/messages/LLDP_m.h"
#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/controllerApps/LLDPMibGraph.h"
#include "openflow/messages/OFP_Features_Reply_m.h"
#include "openflow/messages/OFP_Packet_In_m.h"
#include "openflow/hyperflow/HyperFlowAgent.h"
#include "openflow/hyperflow/HF_ReFire_Wrapper.h"
#include "openflow/utility/LLDP_Wrapper.h"

namespace openflow{

class HF_LLDPAgent:public LLDPAgent {


public:
    HF_LLDPAgent();
    ~HF_LLDPAgent();
    LLDPMibGraph * getMibGraph();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    void handlePacketIn(OFP_Packet_In * packet_in_msg) override;
    HyperFlowAgent * hfAgent;
    simsignal_t HyperFlowReFireSignalId;
};

} /*end namespace openflow*/

#endif
