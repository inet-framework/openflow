
#ifndef OF_CONTROLLER_H_
#define OF_CONTROLLER_H_

#include "TCPSocket.h"
#include "Open_Flow_Message_m.h"
#include "OFP_Packet_In_m.h"
#include "OFP_Hello_m.h"
#include "Switch_Info.h"
#include <omnetpp.h>

class AbstractControllerApp;

class OF_Controller: public cSimpleModule
{
public:
    OF_Controller();
    ~OF_Controller();
    virtual void finish();

    void sendPacketOut(Open_Flow_Message *of_msg, TCPSocket * socket);

    void registerApp(AbstractControllerApp * app);

    TCPSocket *findSocketFor(cMessage *msg) const;
    Switch_Info *findSwitchInfoFor(cMessage *msg) ;
    TCPSocket *findSocketForChassisId(std::string chassisId) const;

    std::vector<Switch_Info >* getSwitchesList() ;
    std::vector<AbstractControllerApp *>* getAppList() ;



protected:
    simsignal_t PacketInSignalId;
    simsignal_t PacketOutSignalId;
    simsignal_t PacketHelloSignalId;
    simsignal_t PacketFeatureRequestSignalId;
    simsignal_t PacketFeatureReplySignalId;
    simsignal_t BootedSignalId;

    //stats
    simsignal_t queueSize;
    simsignal_t waitingTime;
    long numPacketIn;
    std::map<int,int> packetsPerSecond;

    int lastQueueSize;
    double lastChangeTime;
    std::map<int,double> avgQueueSize;

    bool busy;
    double serviceTime;
    std::list<cMessage *> msgList;

    std::vector<Switch_Info > switchesList;
    std::vector<AbstractControllerApp *> apps;

    TCPSocket socket;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void processQueuedMsg(cMessage *data_msg);
    void calcAvgQueueSize(int size);
    void sendHello(Open_Flow_Message *msg);
    void registerConnection(Open_Flow_Message *msg);
    void sendFeatureRequest(cMessage *msg);
    virtual void handleFeaturesReply(Open_Flow_Message *of_msg);
    virtual void handlePacketIn(Open_Flow_Message *of_msg);
};



#endif /* OF_CONTROLLER_H_ */
