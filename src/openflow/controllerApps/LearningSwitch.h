
#ifndef LEARNINGSWITCH_H_
#define LEARNINGSWITCH_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "MACAddress.h"

class LearningSwitch:public AbstractControllerApp {


public:
    LearningSwitch();
    ~LearningSwitch();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    void doSwitching(OFP_Packet_In *packet_in_msg);

    std::map<Switch_Info *,std::map<MACAddress,uint32_t> > lookupTable;

    int idleTimeout;
    int hardTimeout;


};


#endif
