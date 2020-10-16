

package openflow.hostApps;


import inet.applications.contract.ITCPApp;


simple TCPTrafficSinkApp like ITCPApp
{
    parameters:
        @class(openflow::TCPTrafficSinkApp);
        @display("i=block/app");
        string localAddress = default("");
        int localPort = default(-1);  // local port

    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}

