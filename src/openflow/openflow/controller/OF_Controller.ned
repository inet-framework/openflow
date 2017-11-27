

package openflow.openflow.controller;

//Communication with OpenFlow switch;
//Sending Packet-Out messages;
//Sending Flow Modification messages;

simple OF_Controller
{
    parameters:
        @signal[queueSize](type="long");
        @statistic[queueSize](title="QueueSize"; record=vector?,stats?; interpolationmode=none);
        @signal[waitingTime](type="simtime_t");
        @statistic[waitingTime](title="WaitingTime"; record=vector?,stats?; interpolationmode=none);
        @display("i=block/app");
        
        string address = default("");
        int port = default(6633);
        double serviceTime @unit("s") = default(0s);
        
    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}
