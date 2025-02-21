
#ifndef OF_CONTROLLER_H_
#define OF_CONTROLLER_H_

#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include "openflow/messages/Open_Flow_Message_m.h"
#include "openflow/messages/OFP_Packet_In_m.h"
#include "openflow/messages/OFP_Hello_m.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"


namespace openflow{

class AbstractControllerApp;

class OF_Controller: public OperationalBase, public TcpSocket::BufferingCallback
{
public:
    OF_Controller();
    ~OF_Controller();
    virtual void finish() override;

    void sendPacketOut(Packet *of_msg, TcpSocket * socket);

    void registerApp(AbstractControllerApp * app);

    TcpSocket *findSocketFor(cMessage *) const;
    Switch_Info *findSwitchInfoFor(cMessage *msg) ;
    TcpSocket *findSocketForChassisId(std::string chassisId) const;

    std::vector<Switch_Info >* getSwitchesList() ;
    std::vector<AbstractControllerApp *>* getAppList() ;

    virtual void sendPacket(TcpSocket *tcp, Packet *msg);


protected:
    /**
     * Observer Signals
     */
    static simsignal_t PacketInSignalId;
    static simsignal_t PacketOutSignalId;
    static simsignal_t PacketHelloSignalId;
    static simsignal_t PacketFeatureRequestSignalId;
    static simsignal_t PacketFeatureReplySignalId;
    static simsignal_t PacketExperimenterSignalId;
    static simsignal_t BootedSignalId;

    /**
     * Statistics
     */
    simsignal_t queueSize;
    simsignal_t waitingTime;
    long numPacketIn;
    std::map<int,int> packetsPerSecond;

    int lastQueueSize;
    double lastChangeTime;
    std::map<int,double> avgQueueSize;

    /**
     * Message Processing
     */
    bool booted = false;
    bool busy;
    bool parallelProcessing;
    double serviceTime;
    struct Action
    {
        int kind;
        cMessage *msg;
        Action() : kind(0), msg(nullptr) {}
        Action(int kind, cMessage* msg) : kind(kind), msg(msg) {}
    };
    std::list<Action> msgList;

    /**
     * Network and Controller State
     */
    std::vector<Switch_Info > switchesList;
    std::vector<AbstractControllerApp *> apps;

    /**
     * Connection
     */
    TcpSocket socket;

    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    void processQueuedMsg(cMessage *);
    void processPacketFromTcp(Packet *pkt);
    void startProcessingMsg(Action& action);
    void calcAvgQueueSize(int size);
    void sendHello(Packet *msg);
    virtual void registerConnection(Indication *sockInfo);
    void sendFeatureRequest(Packet *msg);
    virtual void handleFeaturesReply(Packet *of_msg);
    virtual void handlePacketIn(Packet *of_msg);
    virtual void handleExperimenter(Packet* of_msg);

    /** @name TcpSocket::ICallback callback methods */
    //@{
    virtual void socketDataArrived(TcpSocket *socket) override;
    virtual void socketAvailable(TcpSocket *socket, TcpAvailableInfo *availableInfo) override;
    virtual void socketEstablished(TcpSocket *socket) override;
    virtual void socketPeerClosed(TcpSocket *socket) override;
    virtual void socketClosed(TcpSocket *socket) override;
    virtual void socketFailure(TcpSocket *socket, int code) override;
    virtual void socketStatusArrived(TcpSocket *socket, TcpStatusInfo *status) override {}
    virtual void socketDeleted(TcpSocket *socket) override {} // TODO
    //@}

    /** @name Lifecycle methods */
    //@{
    virtual void handleStartOperation(LifecycleOperation *operation) override;
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
    //@}
};

} /*end namespace openflow*/

#endif /* OF_CONTROLLER_H_ */
