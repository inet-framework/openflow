
#ifndef LEARNINGSWITCH_H_
#define LEARNINGSWITCH_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "inet/linklayer/common/MACAddress.h"

namespace openflow{

class LearningSwitch:public AbstractControllerApp {


public:
    LearningSwitch();
    ~LearningSwitch();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    void doSwitching(OFP_Packet_In *packet_in_msg);

    std::map<Switch_Info *,std::map<MACAddress,uint32_t> > lookupTable;

    int idleTimeout;
    int hardTimeout;


};

} /*end namespace openflow*/

#endif
