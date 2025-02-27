
package openflow.openflow.controller;

//
// Interface for OpenFlow controller implementations.
//
// The OpenFlow controller is responsible for:
//
// 1. Establishing and maintaining connections with OpenFlow switches
// 2. Processing OpenFlow protocol messages (HELLO, FEATURES_REQUEST, PACKET_IN, etc.)
// 3. Managing the network by installing flow entries in switches
// 4. Providing an interface for controller applications to implement network control logic
//
moduleinterface IOpenFlowController
{
    parameters:
        // IP address the controller listens on
        string address;

        // TCP port the controller listens on (standard OpenFlow port is 6633)
        int port;

        // Processing time for each message (used to simulate controller processing delay)
        double serviceTime @unit("s");

        // Time before the controller is fully operational (boot delay)
        double bootTime @unit("s");

    gates:
        input socketIn @labels(TcpCommand/up);
        output socketOut @labels(TcpCommand/down);
}
