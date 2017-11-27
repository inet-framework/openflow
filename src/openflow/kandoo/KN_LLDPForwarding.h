
#ifndef KNLLDPAGENTFORWARDING_H_
#define KNLLDPAGENTFORWARDING_H_

#include <omnetpp.h>
#include "LLDPForwarding.h"
#include "KandooAgent.h"




class KN_LLDPForwarding:public LLDPForwarding {


public:
    KN_LLDPForwarding();
    ~KN_LLDPForwarding();

protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    virtual void handlePacketIn(OFP_Packet_In * packet_in_msg);

    KandooAgent * knAgent;
    simsignal_t kandooEventSignalId;
    simsignal_t cpPingPacketHash;
    std::string appName;


};


#endif
