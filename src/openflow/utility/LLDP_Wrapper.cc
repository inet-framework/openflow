#include "openflow/utility/LLDP_Wrapper.h"

using namespace std;

namespace openflow{

LLDP_Wrapper::LLDP_Wrapper(){

}


LLDP_Wrapper::~LLDP_Wrapper(){

}


const string& LLDP_Wrapper::getDstId() const{
    return this->dstId;
}

void LLDP_Wrapper::setDstId(const string& dstId){
    this->dstId = dstId;
}

int LLDP_Wrapper::getDstPort() const{
    return this->dstPort;
}

void LLDP_Wrapper::setDstPort(int dstPort){
    this->dstPort = dstPort;
}

const string& LLDP_Wrapper::getSrcId() const{
    return this->srcId;
}

void LLDP_Wrapper::setSrcId(const string& srcId){
    this->srcId = srcId;
}
int LLDP_Wrapper::getSrcPort() const{
    return this->srcPort;
}

void LLDP_Wrapper::setSrcPort(int srcPort){
    this->srcPort = srcPort;
}

} /*end namespace openflow*/
