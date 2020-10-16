
#ifndef HYPERFLOWSYNCHRONIZER_H_
#define HYPERFLOWSYNCHRONIZER_H_

#include "inet/transportlayer/contract/tcp/TCPSocket.h"
#include <omnetpp.h>
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/messages/HF_ReportIn_m.h"
#include "openflow/messages/HF_SyncRequest_m.h"
#include "openflow/messages/HF_SyncReply_m.h"
#include "openflow/messages/HF_ChangeNotification_m.h"
#include "openflow/hyperflow/HyperFlowStructs.h"


namespace openflow{

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

} /*end namespace openflow*/

#endif /* OF_CONTROLLER_H_ */
