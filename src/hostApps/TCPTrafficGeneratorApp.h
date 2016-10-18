

#ifndef TCP_TRAFFIC_GENERATOR_APP_H_
#define TCP_TRAFFIC_GENERATOR_APP_H_

#include "INETDefs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <TCPSocket.h>
#include "IPvXAddress.h"

using namespace std;
/**
 * Single-connection TCP application.
 */

struct Stats{
    SimTime connectionStarted;
    SimTime connectionEstablished;
    SimTime connectionFinished;
    long transmittedBytes;
};

class INET_API TCPTrafficGeneratorApp : public cSimpleModule, public TCPSocket::CallbackInterface
{

  protected:
    cTopology topo;
    int  lineNumbers;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    unsigned int FileRead( istream & is, vector <char> & buff );
    unsigned int CountLines( const vector <char> & buff, int sz );
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);
    virtual void socketEstablished(int connId, void *yourPtr);
    virtual void socketPeerClosed(int connId, void *yourPtr);
    virtual void socketClosed(int connId, void *yourPtr);
    virtual void socketFailure(int connId, void *yourPtr, int code);
    virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status);
    std::map<TCPSocket *,Stats> statistics;


    //stats
    simsignal_t connectionFinished;
    simsignal_t connectionStarted;
    simsignal_t connectionEstablished;
    simsignal_t transmittedBytes;


};

#endif

