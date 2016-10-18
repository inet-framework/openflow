
#ifndef ARPRESPONDER_H_
#define ARPRESPONDER_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "OFP_Features_Reply_m.h"
#include "OFP_Packet_In_m.h"
#include "ARPPacket_m.h"


class ARPResponder:public AbstractControllerApp {


public:
    ARPResponder();
    ~ARPResponder();
    virtual void finish();

    bool addEntry(std::string srcIp, MACAddress srcMac);

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg);

    virtual EtherFrame * createArpReply(IPv4Address srcIp, IPv4Address dstIp, MACAddress srcMac,MACAddress dstMac);

    std::map<MACAddress,std::string> macToIp;
    std::map<std::string,MACAddress> ipToMac;

    long answeredArp;
    long floodedArp;
};


#endif
