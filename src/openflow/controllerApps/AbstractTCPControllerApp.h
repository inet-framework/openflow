
#ifndef ABSTRACTTCPCONTROLLERAPP_H_
#define ABSTRACTTCPCONTROLLERAPP_H_

#include "openflow/controllerApps/AbstractControllerApp.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"

namespace openflow{

class AbstractTCPControllerApp: public AbstractControllerApp, public TcpSocket::BufferingCallback
{
protected:
    enum ActionKind {ACTION_EVENT=3098, ACTION_DATA};
    struct Action
    {
        int kind;
        cMessage *msg;
        Action() : kind(0), msg(nullptr) {}
        Action(int kind, cMessage* msg) : kind(kind), msg(msg) {}
    };

    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void processQueuedMsg(cMessage *data_msg) = 0;
    virtual void calcAvgQueueSize(int size);
    virtual void finish() override;

    /** @name TcpSocket::ICallback callback methods */
    //@{
    // virtual void socketDataArrived(TcpSocket *socket) override; // should be implement in derived class
    virtual void socketAvailable(TcpSocket *socket, TcpAvailableInfo *availableInfo) override;
    virtual void socketEstablished(TcpSocket *socket) override;
    virtual void socketPeerClosed(TcpSocket *socket) override;
    virtual void socketClosed(TcpSocket *socket) override;
    virtual void socketFailure(TcpSocket *socket, int code) override;
    virtual void socketStatusArrived(TcpSocket *socket, TcpStatusInfo *status) override {}
    virtual void socketDeleted(TcpSocket *socket) override {} // TODO
    //@}

    virtual void processSelfMessage(cMessage *msg);
    void startProcessingMsg(Action& action);
    virtual void processPacketFromTcp(Packet *pkt) = 0;

    //stats
    simsignal_t queueSize;
    simsignal_t waitingTime;

    std::map<int,int> packetsPerSecond;

    int lastQueueSize;
    double lastChangeTime;
    std::map<int,double> avgQueueSize;

    bool busy;
    std::list<Action> msgList;
    double serviceTime;

    TcpSocket socket;

public:
    AbstractTCPControllerApp();
    ~AbstractTCPControllerApp();

};

} /*end namespace openflow*/

#endif
