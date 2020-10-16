
#ifndef KNLLDPAGENTFORWARDING_H_
#define KNLLDPAGENTFORWARDING_H_

#include <omnetpp.h>
#include "openflow/controllerApps/LLDPForwarding.h"
#include "openflow/kandoo/KandooAgent.h"


namespace openflow{

class KN_LLDPForwarding:public LLDPForwarding {


public:
    KN_LLDPForwarding();
    ~KN_LLDPForwarding();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg) override;

    KandooAgent * knAgent;
    simsignal_t kandooEventSignalId;
    simsignal_t cpPingPacketHash;
    std::string appName;


};

} /*end namespace openflow*/

#endif
