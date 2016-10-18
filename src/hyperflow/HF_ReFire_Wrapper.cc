#include "HF_ReFire_Wrapper.h"

using namespace std;

HF_ReFire_Wrapper::HF_ReFire_Wrapper(){

}


HF_ReFire_Wrapper::~HF_ReFire_Wrapper(){

}


const DataChannelEntry& HF_ReFire_Wrapper::getDataChannelEntry() const{
    return this->dataChannelEntry;
}

void HF_ReFire_Wrapper::setDataChannelEntry(const DataChannelEntry& dataEntry){
    this->dataChannelEntry = dataEntry;
}
