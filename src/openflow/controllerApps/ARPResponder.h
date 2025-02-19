
#ifndef ARPRESPONDER_H_
#define ARPRESPONDER_H_

#include <omnetpp.h>
#include "openflow/controllerApps/AbstractControllerApp.h"
#include "inet/transportlayer/contract/tcp/TcpSocket.h"
#include "openflow/openflow/controller/Switch_Info.h"
#include "openflow/messages/OFP_Features_Reply_m.h"
#include "openflow/messages/OFP_Packet_In_m.h"
#include "inet/networklayer/arp/ipv4/ARPPacket_m.h"

namespace openflow{

class ARPResponder:public AbstractControllerApp {


public:
    ARPResponder();
    ~ARPResponder();
    virtual void finish() override;

    bool addEntry(std::string srcIp, MacAddress srcMac);

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *details) override;
    void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg);

    virtual EtherFrame * createArpReply(Ipv4Address srcIp, Ipv4Address dstIp, MacAddress srcMac,MacAddress dstMac);

    std::map<MacAddress,std::string> macToIp;
    std::map<std::string,MacAddress> ipToMac;

    long answeredArp;
    long floodedArp;
};

} /*end namespace openflow*/

#endif
