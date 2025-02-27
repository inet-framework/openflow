
package openflow.openflow.controller;

//
// [GENERATED DOCUMENTATION -- ACCURACY UNVERIFIED]
// The OF_Controller is the core module that implements the OpenFlow controller functionality
// in the openflow simulation model. It handles the communication with OpenFlow switches,
// processes OpenFlow protocol messages, and provides an interface for controller applications.
//
// The OF_Controller is responsible for:
//
// 1. Connection Management: Establishing and maintaining TCP connections with OpenFlow switches.
//    It handles the OpenFlow handshake process (HELLO, FEATURES_REQUEST, FEATURES_REPLY) and
//    maintains information about connected switches.
//
// 2. Message Processing: Processing OpenFlow protocol messages received from switches, such as
//    PACKET_IN, FEATURES_REPLY, and EXPERIMENTER messages. It also sends messages to switches,
//    such as PACKET_OUT and FLOW_MOD messages.
//
// 3. Controller Application Interface: Providing an interface for controller applications to
//    register themselves and receive notifications about OpenFlow events. It emits signals for
//    various events (PacketIn, PacketOut, etc.) that controller applications can subscribe to.
//
// 4. Switch Information Management: Maintaining a list of connected switches and their capabilities,
//    which can be accessed by controller applications.
//
// The OF_Controller is typically used as a submodule within the Open_Flow_Controller compound module,
// which combines it with standard networking components (TCP/IP stack, Ethernet interfaces) and
// controller applications to form a complete OpenFlow controller.
//
simple OF_Controller like IOpenFlowController
{
    parameters:
        @class(openflow::OF_Controller);
        @signal[PacketIn](type="cPacket");
        @signal[PacketOut](type="cPacket");
        @signal[PacketHello](type="cPacket");
        @signal[PacketFeatureRequest](type="cPacket");
        @signal[PacketFeatureReply](type="cPacket");
        @signal[PacketExperimenter](type="cPacket");
        @signal[Booted](type="openflow::OF_Controller");
        @signal[queueSize](type="unsigned long");
        @statistic[queueSize](title="QueueSize"; record=vector?,stats?; interpolationmode=none);
        @signal[waitingTime](type="simtime_t");
        @statistic[waitingTime](title="WaitingTime"; record=vector?,stats?; interpolationmode=none);
        @display("i=block/app");

        // IP address the controller listens on (empty string means all available interfaces)
        string address = default("");

        // TCP port the controller listens on (standard OpenFlow port is 6633)
        int port = default(6633);

        // Processing time for each message (used to simulate controller processing delay)
        double serviceTime @unit("s") = default(0s);

        // Time before the controller is fully operational (boot delay)
        double bootTime @unit("s") = default(0s);

        // Whether to process messages in parallel (true) or sequentially (false)
        // When false, messages are processed one at a time with serviceTime delay between them
        // When true, multiple messages can be processed simultaneously
		bool parallelProcessing = default(false);

    gates:
        input socketIn @labels(TcpCommand/up);
        output socketOut @labels(TcpCommand/down);
}
