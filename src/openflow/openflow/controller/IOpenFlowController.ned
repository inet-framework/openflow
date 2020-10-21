

package openflow.openflow.controller;

//Interface module for the OpenFlow Controller module.
//Communication with OpenFlow switch;
//Sending Packet-Out messages;
//Sending Flow Modification messages;

moduleinterface IOpenFlowController
{
    parameters:
        
        string address;// = default("");
        int port;// = default(6633);
        double serviceTime @unit("s");// = default(0s);
        double bootTime @unit("s");// = default(0s);
        
    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}
