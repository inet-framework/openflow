#include <omnetpp.h>
#include "openflow/openflow/switch/Buffer.h"
#include "openflow/openflow/protocol/OpenFlow.h"
#include "inet/linklayer/ethernet/common/EthernetMacHeader_m.h"

using namespace std;
using namespace inet;

namespace openflow{

Buffer::Buffer(){

}

Buffer::Buffer(int cap){
    capacity = cap;
    next_buffer_id = 1;
}

Buffer::~Buffer(){
    for(auto&& pair : pending_msgs) {
      delete pair.second;
    }
    pending_msgs.clear();
}

int Buffer::size(){
    return pending_msgs.size();
}

bool Buffer::isfull(){
    return pending_msgs.size() >= capacity;
}




// store message in buffer and return buffer_id.
uint32_t Buffer::storeMessage(Packet *msg){
    auto header = msg->peekAtFront<EthernetMacHeader>();
    pending_msgs.insert(pair<uint32_t, Packet *> (next_buffer_id, msg));

    // OFP_NO_BUFFER = 0xffffffff;
    if (next_buffer_id != OFP_NO_BUFFER){
        uint32_t result = next_buffer_id;
        next_buffer_id++;
        return result;
    }else{
        next_buffer_id = 0;
        return next_buffer_id;
    }
}
bool Buffer::deleteMessage(Packet *msg){
    bool result = false;
    for (std::map<uint32_t, inet::EthernetIIFrame *>::const_iterator it = pending_msgs.begin(); it != pending_msgs.end(); ++it) {
      if (it->second == msg) {
          pending_msgs.erase(it);
          result = true;
      }
    }

    return result;
}


uint32_t Buffer::getCapacity(){
    return capacity;
}

// return message that is stored at the specified buffer_id
Packet *Buffer::returnMessage(uint32_t buffer_id){
    auto it = pending_msgs.find(buffer_id);
    Packet *frame = nullptr;
    if (it != pending_msgs.end()) {
        frame = it->second;
        pending_msgs.erase(it);
    }
    return frame;
}

} /*end namespace openflow*/
