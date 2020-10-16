
#ifndef ABSTRACTTCPCONTROLLERAPP_H_
#define ABSTRACTTCPCONTROLLERAPP_H_

#include "openflow/controllerApps/AbstractControllerApp.h"
#include "inet/transportlayer/contract/tcp/TCPSocket.h"

namespace openflow{

class AbstractTCPControllerApp: public AbstractControllerApp {

protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void processQueuedMsg(cMessage *data_msg);
    virtual void calcAvgQueueSize(int size);
    virtual void finish();

    //stats
    simsignal_t queueSize;
    simsignal_t waitingTime;

    std::map<int,int> packetsPerSecond;

    int lastQueueSize;
    double lastChangeTime;
    std::map<int,double> avgQueueSize;

    bool busy;
    std::list<cMessage *> msgList;
    double serviceTime;

    TCPSocket socket;

    TCPSocket *findSocketFor(cMessage *msg);
    std::map< int,TCPSocket * > socketMap;


public:
    AbstractTCPControllerApp();
    ~AbstractTCPControllerApp();

};

} /*end namespace openflow*/

#endif
