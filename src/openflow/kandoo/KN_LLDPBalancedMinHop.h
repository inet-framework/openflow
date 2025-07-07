#ifndef __OPENFLOW_KN_LLDPBALANCEDMINHOP_H
#define __OPENFLOW_KN_LLDPBALANCEDMINHOP_H

#include <omnetpp.h>
#include "openflow/controllerApps/LLDPBalancedMinHop.h"
#include "openflow/kandoo/KandooAgent.h"

namespace openflow {

class KN_LLDPBalancedMinHop : public LLDPBalancedMinHop
{

  public:
    KN_LLDPBalancedMinHop();
    ~KN_LLDPBalancedMinHop();

  protected:
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    virtual void initialize(int stage) override;
    virtual void handlePacketIn(Packet *) override;

    KandooAgent *knAgent;
    simsignal_t kandooEventSignalId;
    std::string appName;

};

} /*end namespace openflow*/

#endif

