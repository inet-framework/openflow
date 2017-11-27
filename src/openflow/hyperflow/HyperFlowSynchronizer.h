
#ifndef HYPERFLOWSYNCHRONIZER_H_
#define HYPERFLOWSYNCHRONIZER_H_

#include "TCPSocket.h"
#include <omnetpp.h>
#include "Switch_Info.h"
#include "HF_ReportIn_m.h"
#include "HF_SyncRequest_m.h"
#include "HF_SyncReply_m.h"
#include "HF_ChangeNotification_m.h"
#include "HyperFlowStructs.h"




class HyperFlowSynchronizer: public cSimpleModule
{
public:
    HyperFlowSynchronizer();
    ~HyperFlowSynchronizer();



protected:

    //stats
    simsignal_t queueSize;
    simsignal_t waitingTime;

    TCPSocket socket;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    std::map< int,TCPSocket * > socketMap;

    std::list<ControlChannelEntry> controlChannel;
    std::list<DataChannelEntry> dataChannel;
    long dataChannelSizeCache;

    double serviceTime;
    std::list<cMessage *> msgList;
    bool busy;

    TCPSocket *findSocketFor(cMessage *msg);
    void handleSyncRequest(HF_SyncRequest *msg);
    void handleChangeNotification(HF_ChangeNotification *msg);
    void handleReportIn(HF_ReportIn *msg);
    void processQueuedMsg(cMessage * msg);

};



#endif /* OF_CONTROLLER_H_ */
