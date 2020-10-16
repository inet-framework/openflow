

#ifndef LLDPMIB_H_
#define LLDPMIB_H_
#include <omnetpp.h>

using namespace __gnu_cxx;
using namespace omnetpp;

namespace openflow{

class LLDPMib {
    public:
        LLDPMib();
        LLDPMib(int sPort, int dPort,std::string sID,std::string dID,SimTime exp);

        std::string getDstId() const;
        void setDstId(std::string dstId);
        int getDstPort() const;
        void setDstPort(int dstPort);
        std::string getSrcId() const;
        void setSrcId(std::string srcId);
        int getSrcPort() const;
        void setSrcPort(int srcPort);
        SimTime getExpiresAt() const;
        void setExpiresAt(SimTime expiresAt);

        bool operator == (const LLDPMib &b) const;

    protected:
        int srcPort;
        int dstPort;
        std::string srcID;
        std::string dstID;
        SimTime expiresAt;
};

} /*end namespace openflow*/

#endif /* FLOW_TABLE_H_ */
