
#ifndef HFARPRESPONDER_H_
#define HFARPRESPONDER_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/messages/OFP_Features_Reply_m.h"
#include "openflow/messages/OFP_Packet_In_m.h"
#include "inet/networklayer/arp/ipv4/ArpPacket_m.h"
#include "openflow/controllerApps/ARPResponder.h"
#include "openflow/hyperflow/HyperFlowAgent.h"
#include "openflow/hyperflow/HF_ReFire_Wrapper.h"
#include "openflow/utility/ARP_Wrapper.h"

namespace openflow{

class HF_ARPResponder: public ARPResponder {


public:
    HF_ARPResponder();
    ~HF_ARPResponder();


protected:
    virtual bool searchHyperFlowAggent();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    virtual void initialize(int stage) override;
    virtual void handlePacketIn(Packet*) override;

    HyperFlowAgent * hfAgent = nullptr;
    static simsignal_t HyperFlowReFireSignalId;
};

} /*end namespace openflow*/


#endif
