#include <Hub.h>

Define_Module(Hub);

Hub::Hub(){

}

Hub::~Hub(){

}

void Hub::initialize(){
    AbstractControllerApp::initialize();
}

void Hub::receiveSignal(cComponent *src, simsignal_t id, cObject *obj) {
    AbstractControllerApp::receiveSignal(src,id,obj);

    if(id == PacketInSignalId){
        EV << "Hub::PacketIn" << '\n';
        if (dynamic_cast<OFP_Packet_In *>(obj) != NULL) {
            OFP_Packet_In *packet_in = (OFP_Packet_In *) obj;
            floodPacket(packet_in);
        }
    }
}

