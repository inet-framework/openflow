

#ifndef CONTROLLERINVOLVEMENTFILTER_H_
#define CONTROLLERINVOLVEMENTFILTER_H_

#include <omnetpp.h>
using namespace omnetpp;

namespace openflow{

class ControllerInvolvementFilter : public cSimpleModule,  public cListener
{
protected:

        //stats
        simsignal_t cpPingPacketHash;

        virtual void initialize(int stage) override;
        virtual void finish() override;
        virtual void handleMessage(cMessage *msg) override;

        virtual void receiveSignal(cComponent *source, simsignal_t signalID, unsigned long l, cObject *details) override;

        std::map<long,int> controllerInvolvements;

};

} /*end namespace openflow*/

#endif
