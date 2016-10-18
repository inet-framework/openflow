
#ifndef TCP_TRAFFIC_SINK_APP_H_
#define TCP_TRAFFIC_SINK_APP_H_

#include "INETDefs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <TCPSocket.h>

using namespace std;
/**
 * Single-connection TCP application.
 */
class INET_API TCPTrafficSinkApp : public cSimpleModule, public TCPSocket::CallbackInterface
{

  protected:
    int localPort;
    const char * localAddress;
    TCPSocket socket;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);
    virtual void socketEstablished(int connId, void *yourPtr);
    virtual void socketPeerClosed(int connId, void *yourPtr);
    virtual void socketClosed(int connId, void *yourPtr);
    virtual void socketFailure(int connId, void *yourPtr, int code);
    virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status);

};

#endif

