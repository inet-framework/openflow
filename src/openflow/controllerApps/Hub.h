
#ifndef HUB_H_
#define HUB_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"

class Hub:public AbstractControllerApp {


public:
    Hub();
    ~Hub();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
};


#endif
