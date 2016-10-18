

package openflow.hostApps;


import inet.applications.ITCPApp;



simple TCPTrafficSinkApp like ITCPApp
{
    parameters:
		@display("i=block/app");
        string localAddress = default("");
        int localPort = default(-1);  // local port
        
    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}

