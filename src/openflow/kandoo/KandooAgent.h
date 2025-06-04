
#ifndef KANDOO_AGENT_H_
#define KANDOO_AGENT_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractTCPControllerApp.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include "openflow/messages/KN_Packet_m.h"

namespace openflow{

struct SwitchControllerMapping {
    std::string switchId;
    std::string controllerId;
    TcpSocket *socket;
};

class KandooAgent:public AbstractTCPControllerApp {


public:
    KandooAgent();
    ~KandooAgent();

    bool getIsRootController();

    void sendRequest(KandooEntry entry);
    void sendReply(KN_Packet * knpck,KandooEntry entry);

    void handleKandooPacket(KN_Packet * knpck);

    void sendReplyToSwitchAuthoritive(std::string switchId, KandooEntry entry);

protected:

    void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void processQueuedMsg(cMessage *data_msg);

    bool isRootController;

    std::list<SwitchControllerMapping> switchControllerMapping;

    simsignal_t kandooEventSignalId;


};

} /*end namespace openflow*/


#endif
