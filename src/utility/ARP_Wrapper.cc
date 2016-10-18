#include "ARP_Wrapper.h"

using namespace std;

ARP_Wrapper::ARP_Wrapper(){

}


ARP_Wrapper::~ARP_Wrapper(){

}

const string& ARP_Wrapper::getSrcIp() const {
    return this->srcIp;
}

void ARP_Wrapper::setSrcIp(const string& srcIp){
    this->srcIp = srcIp;
}

const MACAddress& ARP_Wrapper::getSrcMacAddress() const{
    return this->srcMac;
}

void ARP_Wrapper::setSrcMacAddress(const MACAddress& macAddress){
    this->srcMac = macAddress;
}
