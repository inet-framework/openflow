

#ifndef BUFFER_H_
#define BUFFER_H_

#include <deque>
#include <map>
#include <EtherFrame_m.h>


using namespace std;

class Buffer {

public:
    Buffer();
    Buffer(int cap);
    ~Buffer();
    bool isfull();
    uint32_t storeMessage(EthernetIIFrame *msg);
    bool deleteMessage(EthernetIIFrame *msg);
    EthernetIIFrame *returnMessage(uint32_t buffer_id);
    uint32_t getCapacity();
    int size();


protected:
    std::map<uint32_t, EthernetIIFrame *> pending_msgs;
    uint32_t capacity;
    uint32_t next_buffer_id;
};




#endif /* BUFFER_H_ */
