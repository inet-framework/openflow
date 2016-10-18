

#ifndef CONTROLLERINVOLVEMENTFILTER_H_
#define CONTROLLERINVOLVEMENTFILTER_H_

#include <omnetpp.h>

class ControllerInvolvementFilter : public cSimpleModule,  public cListener
{
protected:

        //stats
        simsignal_t cpPingPacketHash;

        virtual void initialize(int stage);
        virtual void finish();
        virtual void handleMessage(cMessage *msg);

        virtual void receiveSignal(cComponent *source, simsignal_t signalID, unsigned long l);

        std::map<long,int> controllerInvolvements;

};


#endif
