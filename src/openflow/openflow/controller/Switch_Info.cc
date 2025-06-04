#include <omnetpp.h>
#include "openflow/openflow/controller/Switch_Info.h"

using namespace std;

namespace openflow{

Switch_Info::Switch_Info(){

}


int Switch_Info::getConnId() const {
        return connID;
}

void Switch_Info::setConnId(int connId) {
        connID = connId;
}

int Switch_Info::getVersion() const {
        return connID;
}

void Switch_Info::setVersion(int version) {
        this->version = version;
}


string Switch_Info::getMacAddress() const {
        return macAddress;
}

void Switch_Info::setMacAddress(string macAddress) {
        this->macAddress = macAddress;
}

int Switch_Info::getNumOfPorts() const {
        return numOfPorts;
}

void Switch_Info::setNumOfPorts(int numOfPorts) {
        this->numOfPorts = numOfPorts;
}

TcpSocket* Switch_Info::getSocket() const {
        return socket;
}

void Switch_Info::setSocket(TcpSocket* socket) {
        this->socket = socket;
}

} /*end namespace openflow*/
