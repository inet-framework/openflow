#ifndef __OPENFLOW_HF_REFIRE_WRAPPER_H
#define __OPENFLOW_HF_REFIRE_WRAPPER_H

#include <omnetpp.h>
#include "inet/linklayer/common/MacAddress.h"
#include "openflow/hyperflow/HyperFlowStructs.h"

using namespace std;

namespace openflow {

class HF_ReFire_Wrapper : public cObject
{

  public:
    HF_ReFire_Wrapper();
    ~HF_ReFire_Wrapper();

    const DataChannelEntry& getDataChannelEntry() const;
    void setDataChannelEntry(const DataChannelEntry& dataEntry);

  protected:
    DataChannelEntry dataChannelEntry;
};

} /*end namespace openflow*/

#endif

