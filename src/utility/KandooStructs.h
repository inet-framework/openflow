
#ifndef KANDOOSTRUCTS_H_
#define KANDOOFLOWSTRUCTS_H_


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



#endif /* OF_CONTROLLER_H_ */
