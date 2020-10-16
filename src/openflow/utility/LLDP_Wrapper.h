

#ifndef LLDP_WRAPPER_H_
#define LLDP_WRAPPER_H_

#include <omnetpp.h>

using namespace std;
using namespace omnetpp;

namespace openflow{

class LLDP_Wrapper: public cObject {

public:
    LLDP_Wrapper();
    ~LLDP_Wrapper();

    const string& getDstId() const;
    void setDstId(const string& dstId);
    int getDstPort() const;
    void setDstPort(int dstPort);
    const string& getSrcId() const;
    void setSrcId(const string& srcId);
    int getSrcPort() const;
    void setSrcPort(int srcPort);


protected:
    string dstId;
    string srcId;
    int dstPort;
    int srcPort;

};


} /*end namespace openflow*/

#endif /* BUFFER_H_ */
