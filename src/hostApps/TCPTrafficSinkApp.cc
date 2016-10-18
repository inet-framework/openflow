

#include "TCPTrafficSinkApp.h"
#include "IPvXAddress.h"
#include "TCPSocket.h"
#include "IPvXAddressResolver.h"

using namespace std;


Define_Module(TCPTrafficSinkApp);


void TCPTrafficSinkApp::initialize(){
    //init params
    localAddress = par("localAddress");
    localPort = par("localPort");

    socket.setOutputGate(gate("tcpOut"));
    socket.setDataTransferMode(TCP_TRANSFER_OBJECT);
    socket.bind(localAddress[0] ? IPvXAddress(localAddress) : IPvXAddress(), localPort);
    socket.listen();
    socket.setCallbackObject(this,&socket);
}





void TCPTrafficSinkApp::handleMessage(cMessage *msg){
    if(!msg->isSelfMessage()){
       if(TCPSocket::belongsToAnyTCPSocket(msg)){
           TCPSocket * tempSocket = new TCPSocket(msg);
           tempSocket->setOutputGate(gate("tcpOut"));
           tempSocket->setDataTransferMode(TCP_TRANSFER_OBJECT);
           tempSocket->setCallbackObject(this,tempSocket);
           tempSocket->processMessage(msg);
           delete tempSocket;
       }
    } else {
        delete msg;
    }
}

void TCPTrafficSinkApp::socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent){
    EV<< "TCPSinkApp all Data Arrived -> Close" << endl;
    if (static_cast<TCPSocket *>(yourPtr) != NULL) {
            TCPSocket *tempSocket = (TCPSocket *)yourPtr;
            tempSocket->close();
    }

    delete msg;
}

void TCPTrafficSinkApp::socketEstablished(int connId, void *yourPtr) {
    EV<< "TCPSinkApp Connection Established" << endl;
}

void TCPTrafficSinkApp::socketPeerClosed(int connId, void *yourPtr) {
    EV<< "TCPSinkApp Peer Closed -> Closing Too" << endl;
}

void TCPTrafficSinkApp::socketClosed(int connId, void *yourPtr) {
    EV<< "TCPSinkApp Socket Closed" << endl;
}

void TCPTrafficSinkApp::socketFailure(int connId, void *yourPtr, int code) {
    EV<< "TCPSinkApp Socket Failed" << endl;
    if (code==TCP_I_CONNECTION_RESET)
        EV << "Connection reset!\\n";
    else if (code==TCP_I_CONNECTION_REFUSED)
        EV << "Connection refused!\\n";
    else if (code==TCP_I_TIMED_OUT)
        EV << "Connection timed out!\\n";
}

void TCPTrafficSinkApp::socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {
    EV<< "TCPSinkApp Status Arrived" << endl;
    delete status;
}






