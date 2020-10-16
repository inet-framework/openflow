
#ifndef KNARPRESPONDER_H_
#define KNARPRESPONDER_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/messages/OFP_Features_Reply_m.h"
#include "openflow/messages/OFP_Packet_In_m.h"
#include "inet/networklayer/arp/ipv4/ARPPacket_m.h"
#include "openflow/controllerApps/ARPResponder.h"
#include "openflow/kandoo/KandooAgent.h"
#include "openflow/utility/ARP_Wrapper.h"

namespace openflow{

class KN_ARPResponder:public ARPResponder {


public:
    KN_ARPResponder();
    ~KN_ARPResponder();


protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    void handlePacketIn(OFP_Packet_In * packet_in_msg) override;

    KandooAgent * knAgent;
    simsignal_t kandooEventSignalId;
    std::string appName;
};

} /*end namespace openflow*/

#endif
