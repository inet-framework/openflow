#include "openflow/hyperflow/HF_ReFire_Wrapper.h"

using namespace std;

namespace openflow {

Register_Class(HF_ReFire_Wrapper);

HF_ReFire_Wrapper::HF_ReFire_Wrapper() = default;

HF_ReFire_Wrapper::~HF_ReFire_Wrapper() = default;

const DataChannelEntry& HF_ReFire_Wrapper::getDataChannelEntry() const {
    return this->dataChannelEntry;
}

void HF_ReFire_Wrapper::setDataChannelEntry(const DataChannelEntry& dataEntry) {
    this->dataChannelEntry = dataEntry;
}

} /*end namespace openflow*/

