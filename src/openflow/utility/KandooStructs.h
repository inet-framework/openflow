
#ifndef KANDOOSTRUCTS_H_
#define KANDOOSTRUCTS_H_

namespace openflow{

struct KandooEntry{
    std::string srcController;
    std::string trgController;
    std::string trgApp;
    std::string srcApp;
    std::string trgSwitch;
    std::string srcSwitch;
    cObject * payload;
    int type; //0 inform, 1 request, 2 reply
};

} /*end namespace openflow*/

#endif /* OF_CONTROLLER_H_ */
