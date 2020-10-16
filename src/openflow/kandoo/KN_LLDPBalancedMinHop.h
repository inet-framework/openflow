
#ifndef KNLLDPBALANCEDMINHOP_H_
#define KNLLDPBALANCEDMINHOP_H_

#include <omnetpp.h>
#include "openflow/controllerApps/LLDPBalancedMinHop.h"
#include "openflow/kandoo/KandooAgent.h"


namespace openflow{

class KN_LLDPBalancedMinHop:public LLDPBalancedMinHop {


public:
    KN_LLDPBalancedMinHop();
    ~KN_LLDPBalancedMinHop();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg) override;

    KandooAgent * knAgent;
    simsignal_t kandooEventSignalId;
    std::string appName;


};

} /*end namespace openflow*/

#endif
