
#ifndef KNARPRESPONDER_H_
#define KNARPRESPONDER_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "OFP_Features_Reply_m.h"
#include "OFP_Packet_In_m.h"
#include "ARPPacket_m.h"
#include "ARPResponder.h"
#include "KandooAgent.h"
#include "ARP_Wrapper.h"


class KN_ARPResponder:public ARPResponder {


public:
    KN_ARPResponder();
    ~KN_ARPResponder();


protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    void handlePacketIn(OFP_Packet_In * packet_in_msg);

    KandooAgent * knAgent;
    simsignal_t kandooEventSignalId;
    std::string appName;
};


#endif
