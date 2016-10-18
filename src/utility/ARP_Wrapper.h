

#ifndef ARP_WRAPPER_H_
#define ARP_WRAPPER_H_

#include "cobject.h"
#include "MACAddress.h"

using namespace std;

class ARP_Wrapper: public cObject {

public:
    ARP_Wrapper();
    ~ARP_Wrapper();

    const string& getSrcIp() const;
    void setSrcIp(const string& srcIp);

    const MACAddress& getSrcMacAddress() const;
    void setSrcMacAddress(const MACAddress& macAddress);



protected:
    string srcIp;
    MACAddress srcMac;
};




#endif /* BUFFER_H_ */
