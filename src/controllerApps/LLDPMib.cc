#include <omnetpp.h>
#include "LLDPMib.h"

using namespace std;

LLDPMib::LLDPMib(){

}

LLDPMib::LLDPMib(int sPort, int dPort,std::string sID,std::string dID,SimTime exp){
    srcPort = sPort;
    dstPort = dPort;
    srcID = sID;
    dstID = dID;
    expiresAt = exp;
}

bool LLDPMib::operator == ( const LLDPMib &b) const{
    return ((strcmp(b.getDstId().c_str(),dstID.c_str())==0
            && strcmp(b.getSrcId().c_str(),srcID.c_str())==0
            && b.getDstPort() == dstPort
            && b.getSrcPort() == srcPort)
            || (strcmp(b.getDstId().c_str(),srcID.c_str())==0
                    && strcmp(b.getSrcId().c_str(),dstID.c_str())==0
                    && b.getDstPort() == srcPort
                    && b.getSrcPort() == dstPort));
}

string LLDPMib::getDstId() const{
    return dstID;
}

void LLDPMib::setDstId(string dstId){
    this->dstID = dstId;
}

int LLDPMib::getDstPort() const{
    return dstPort;
}

void LLDPMib::setDstPort(int dstPort){
    this->dstPort = dstPort;
}

string LLDPMib::getSrcId() const{
    return srcID;
}

void LLDPMib::setSrcId(string srcId){
    this->srcID = srcId;
}

int LLDPMib::getSrcPort() const{
    return srcPort;
}

void LLDPMib::setSrcPort(int srcPort){
    this->srcPort = srcPort;
}

SimTime LLDPMib::getExpiresAt() const{
    return expiresAt;
}

void LLDPMib::setExpiresAt(SimTime expiresAt){
    this->expiresAt = expiresAt;
}
