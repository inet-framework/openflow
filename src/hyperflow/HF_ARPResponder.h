
#ifndef HFARPRESPONDER_H_
#define HFARPRESPONDER_H_

#include <omnetpp.h>
#include "AbstractControllerApp.h"
#include "TCPSocket.h"
#include "Switch_Info.h"
#include "OFP_Features_Reply_m.h"
#include "OFP_Packet_In_m.h"
#include "ARPPacket_m.h"
#include "ARPResponder.h"
#include "HyperFlowAgent.h"
#include "HF_ReFire_Wrapper.h"
#include "ARP_Wrapper.h"


class HF_ARPResponder:public ARPResponder {


public:
    HF_ARPResponder();
    ~HF_ARPResponder();


protected:
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
    void initialize();
    void handlePacketIn(OFP_Packet_In * packet_in_msg);

    HyperFlowAgent * hfAgent;
    simsignal_t HyperFlowReFireSignalId;
};


#endif
