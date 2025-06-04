
#ifndef HYPERFLOWSYNCHRONIZER_H_
#define HYPERFLOWSYNCHRONIZER_H_

#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/messages/HF_ReportIn_m.h"
#include "openflow/messages/HF_SyncRequest_m.h"
#include "openflow/messages/HF_SyncReply_m.h"
#include "openflow/messages/HF_ChangeNotification_m.h"
#include "openflow/hyperflow/HyperFlowStructs.h"


namespace openflow{

class HyperFlowSynchronizer: public OperationalBase
{
public:
    HyperFlowSynchronizer();
    ~HyperFlowSynchronizer();



protected:

    //stats
    simsignal_t queueSize;
    simsignal_t waitingTime;

    TcpSocket socket;

    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;

    std::map< int,TcpSocket * > socketMap;

    std::list<ControlChannelEntry> controlChannel;
    std::list<DataChannelEntry> dataChannel;
    long dataChannelSizeCache;

    double serviceTime;
    std::list<cMessage *> msgList;
    bool busy;

    TcpSocket *findSocketFor(cMessage *msg);
    void handleSyncRequest(Packet *msg);
    void handleChangeNotification(Packet *msg);
    void handleReportIn(Packet *msg);
    void processQueuedMsg(Packet * msg);


    // Lifecycle methods
    virtual void handleStartOperation(LifecycleOperation *operation) override {};
    virtual void handleStopOperation(LifecycleOperation *operation) override {};
    virtual void handleCrashOperation(LifecycleOperation *operation) override {};

#if INET_VERSION >= 0x0404
    virtual bool isInitializeStage(int stage) const override { return stage == INITSTAGE_APPLICATION_LAYER; }
    virtual bool isModuleStartStage(int stage) const override { return stage == ModuleStartOperation::STAGE_APPLICATION_LAYER; }
    virtual bool isModuleStopStage(int stage) const override { return stage == ModuleStopOperation::STAGE_APPLICATION_LAYER; }
#else
    virtual bool isInitializeStage(int stage) override { return stage == INITSTAGE_APPLICATION_LAYER; }
    virtual bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_APPLICATION_LAYER; }
    virtual bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_APPLICATION_LAYER; }
#endif
};

} /*end namespace openflow*/

#endif /* OF_CONTROLLER_H_ */
