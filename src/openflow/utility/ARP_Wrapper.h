#ifndef __OPENFLOW_ARP_WRAPPER_H
#define __OPENFLOW_ARP_WRAPPER_H

#include <omnetpp.h>
#include "inet/linklayer/common/MacAddress.h"

using namespace std;
using namespace inet;

namespace openflow {

class ARP_Wrapper : public cObject
{

  public:
    ARP_Wrapper();
    ~ARP_Wrapper();

    const string& getSrcIp() const;
    void setSrcIp(const string& srcIp);

    const MacAddress& getSrcMacAddress() const;
    void setSrcMacAddress(const MacAddress& macAddress);

  protected:
    string srcIp;
    MacAddress srcMac;
};

} /*end namespace openflow*/

#endif

