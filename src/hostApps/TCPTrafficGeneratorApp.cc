

#include "TCPTrafficGeneratorApp.h"
#include "TCPSocket.h"
#include "IPvXAddressResolver.h"

using namespace std;


Define_Module(TCPTrafficGeneratorApp);


void TCPTrafficGeneratorApp::initialize(){
    topo.extractByNedTypeName(cStringTokenizer(par("destinationNedType")).asVector());

    //determine the first connection setup
    cMessage *msg = new cMessage("newConnection");
    msg->setKind(1);
    scheduleAt((double)par("startSending"), msg);


    //stats
    connectionFinished =registerSignal("connectionFinished");
    connectionStarted = registerSignal("connectionStarted");
    connectionEstablished =registerSignal("connectionEstablished");
    transmittedBytes = registerSignal("transmittedBytes");

    //determine linenumbers
    const int SZ = 1024 * 1024;
    std::vector <char> buff( SZ );
    std::string path = par("pathToFlowSizes");
    ifstream ifs( path.c_str() );
    while( int cc = FileRead( ifs, buff ) ) {
        lineNumbers += CountLines( buff, cc );
    }
    ifs.close();
}





void TCPTrafficGeneratorApp::handleMessage(cMessage *msg){

    if (msg->isSelfMessage()){
        if(msg->getKind() == 1){
            //determine random target
            int random_num = intrand(topo.getNumNodes());
            const char *connectAddress = topo.getNode(random_num)->getModule()->getFullPath().c_str();
            IPvXAddress destAddr = IPvXAddressResolver().resolve(connectAddress);

            while (topo.getNode(random_num)->getModule() == getParentModule() || destAddr.isUnspecified()) {
                // avoid same source and destination
                random_num = intrand(topo.getNumNodes());
                connectAddress = topo.getNode(random_num)->getModule()->getFullPath().c_str();
                destAddr = IPvXAddressResolver().resolve(connectAddress);
            }
            //generate socket
            TCPSocket *tempSocket = new TCPSocket();
            tempSocket->setOutputGate(gate("tcpOut"));
            tempSocket->setDataTransferMode(TCP_TRANSFER_OBJECT);
            tempSocket->setCallbackObject(this,tempSocket);
            int connectPort = par("connectPort");

            tempSocket->connect(destAddr, connectPort);



            //generate packet
            cPacket *packet = new cPacket();
            packet->setKind(TCP_C_SEND);
            int pos = floor(uniform(0,lineNumbers));

            //get the size of the nth line
            std::string path = par("pathToFlowSizes");
            std::ifstream f(path.c_str());
            std::string s;
            for (int i = 1; i <= pos; i++)
                    std::getline(f, s);

            //convert to long
            long size = (long) atof(s.c_str());

            f.close();

            packet->setByteLength(size);

            //send everything
            tempSocket->send(packet);




            //add to map
            Stats temp = Stats();
            temp.connectionStarted=simTime();
            temp.transmittedBytes=size;


            statistics[tempSocket]=temp;


            //schedule next connection
            cMessage *newMsg = new cMessage("newConnection");
            newMsg->setKind(1);
            double rnd = gamma_d(0.4754,13.7300);
            scheduleAt(simTime()+rnd, newMsg);
        }
        delete msg;
    } else {
        if(TCPSocket::belongsToAnyTCPSocket(msg)){
            //find the socket
            std::map<TCPSocket *, Stats>::iterator iterConn;
            TCPSocket * tempSocket = NULL;
            for(iterConn=statistics.begin();iterConn!=statistics.end();iterConn++){
                if(iterConn->first->belongsToSocket(msg)){
                    tempSocket = iterConn->first;
                    break;
                }
            }

            //process the message
            if(tempSocket != NULL){
                tempSocket->processMessage(msg);
            } else {
                error("This should not happen!");
            }

        } else {
            delete msg;
        }
    }
}


void TCPTrafficGeneratorApp::socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent){
    EV<< "TCPTrafficGenerator Data Arrived" << endl;
    delete msg;
}

void TCPTrafficGeneratorApp::socketEstablished(int connId, void *yourPtr) {
    EV<< "TCPTrafficGenerator Connection Established" << endl;
    if (static_cast<TCPSocket *>(yourPtr) != NULL) {
        TCPSocket *tempSocket = (TCPSocket *)yourPtr;
        statistics[tempSocket].connectionEstablished = simTime();
    }
}

void TCPTrafficGeneratorApp::socketPeerClosed(int connId, void *yourPtr) {
    EV<< "TCPTrafficGenerator Peer Closed -> Closing Too" << endl;
    if (static_cast<TCPSocket *>(yourPtr) != NULL) {
        TCPSocket *tempSocket = (TCPSocket *)yourPtr;
        statistics[tempSocket].connectionFinished=simTime();

        //emit vectors
        emit(connectionStarted,statistics[tempSocket].connectionStarted);
        emit(connectionEstablished,statistics[tempSocket].connectionEstablished);
        emit(connectionFinished,statistics[tempSocket].connectionFinished);
        emit(transmittedBytes,statistics[tempSocket].transmittedBytes);

        tempSocket->close();
    }
}

void TCPTrafficGeneratorApp::socketClosed(int connId, void *yourPtr) {
    EV<< "TCPTrafficGenerator Socket Closed" << endl;
    if (static_cast<TCPSocket *>(yourPtr) != NULL) {
            TCPSocket *tempSocket = (TCPSocket *)yourPtr;
            //remove the socket
            statistics.erase(tempSocket);

            //clear up space
            delete tempSocket;
    }
}

void TCPTrafficGeneratorApp::socketFailure(int connId, void *yourPtr, int code) {
    EV<< "TCPTrafficGenerator Socket Failed" << endl;
    if (code==TCP_I_CONNECTION_RESET)
        EV << "Connection reset!\\n";
    else if (code==TCP_I_CONNECTION_REFUSED)
        EV << "Connection refused!\\n";
    else if (code==TCP_I_TIMED_OUT)
        EV << "Connection timed out!\\n";
}

void TCPTrafficGeneratorApp::socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {
    EV<< "TCPTrafficGenerator Status Arrived" << endl;
    delete status;
}



unsigned int TCPTrafficGeneratorApp::FileRead( istream & is, vector <char> & buff ) {
    is.read( &buff[0], buff.size() );
    return is.gcount();
}

unsigned int TCPTrafficGeneratorApp::CountLines( const vector <char> & buff, int sz ) {
    int newlines = 0;
    const char * p = &buff[0];
    for ( int i = 0; i < sz; i++ ) {
        if ( p[i] == '\n' ) {
            newlines++;
        }
    }
    return newlines;
}







