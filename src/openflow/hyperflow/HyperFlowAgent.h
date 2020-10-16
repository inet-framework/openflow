
#ifndef HYPER_FLOW_AGENT_H_
#define HYPER_FLOW_AGENT_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractTCPControllerApp.h"
#include "openflow/messages/HF_SyncRequest_m.h"
#include "openflow/messages/HF_ReportIn_m.h"
#include "openflow/messages/HF_SyncReply_m.h"
#include "openflow/hyperflow/HyperFlowStructs.h"
#include "openflow/messages/HF_ChangeNotification_m.h"
#include "openflow/hyperflow/HF_ReFire_Wrapper.h"

namespace openflow{

class HyperFlowAgent:public AbstractTCPControllerApp {


public:
    HyperFlowAgent();
    ~HyperFlowAgent();
    void synchronizeDataChannelEntry(DataChannelEntry entry);

protected:

    void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void processQueuedMsg(cMessage *data_msg);

    void sendReportIn();
    void sendSyncRequest();
    void handleSyncReply(HF_SyncReply * msg);
    void handleCheckAlive();
    void handleRecover(std::string controllerId);
    void handleFailure(std::string controllerId);


    bool waitingForSyncResponse;
    int lastSyncCounter;

    double checkSyncEvery;
    double checkAliveEvery;
    double checkReportInEvery;

    std::list<ControlChannelEntry> controlChannel;
    std::list<DataChannelEntry> dataChannel;

    std::list<std::string> knownControllers;
    std::list<std::string> failedControllers;

    simsignal_t HyperFlowReFireSignalId;


};


} /*end namespace openflow*/

#endif
