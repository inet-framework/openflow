
package openflow.hyperflow;

//
// [GENERATED DOCUMENTATION -- ACCURACY UNVERIFIED]
// The HyperFlowAgent is a core component of the HyperFlow distributed controller architecture
// for OpenFlow networks. It enables multiple OpenFlow controllers to work together as a logically
// centralized controller while being physically distributed.
//
// HyperFlow is a distributed controller architecture that:
// - Enables multiple OpenFlow controllers to work together as a logically centralized controller
// - Provides fault tolerance and scalability through controller distribution
// - Synchronizes state between controllers using a publish-subscribe mechanism
// - Allows controllers to operate independently while maintaining a consistent network view
//
// HyperFlowAgent's Role:
//
// 1. State Synchronization: The HyperFlowAgent maintains two channels for synchronization:
//    - Control Channel: Contains information about controllers and their connected switches
//    - Data Channel: Contains events and state changes that need to be synchronized
//
// 2. Controller Communication: The HyperFlowAgent connects to a central HyperFlowSynchronizer
//    that facilitates communication between distributed controllers. It periodically:
//    - Reports its status and connected switches (ReportIn)
//    - Requests synchronization with other controllers (SyncRequest)
//    - Checks if other controllers are alive (CheckAlive)
//
// 3. Event Distribution: When state changes occur in one controller (e.g., a new ARP entry),
//    the HyperFlowAgent:
//    - Packages the change as a DataChannelEntry
//    - Sends it to the HyperFlowSynchronizer
//    - The change is then distributed to all other controllers
//
// 4. Event Notification: The HyperFlowAgent emits HyperFlowReFire signals to notify other
//    controller applications (like HF_ARPResponder, HF_LLDPAgent) about state changes from
//    other controllers, allowing them to update their local state.
//
// 5. Fault Tolerance: The HyperFlowAgent detects controller failures and recoveries, enabling
//    the system to continue operating even if some controllers fail.
//
simple HyperFlowAgent extends openflow.controllerApps.AbstractTCPControllerApp
{
    parameters:
        @class(openflow::HyperFlowAgent);
        @class(HyperFlowAgent);
        @signal[HyperFlowReFire];
        @display("i=block/app");

        // Hard timeout for flow entries (0 means no hard timeout)
        int flowModHardTimeOut = default(0);

        // Idle timeout for flow entries (how long a flow entry remains if not used)
        int flowModIdleTimeOut = default(1);

        // Local port for the TCP socket (use -1 for automatic port assignment)
        int localPort = default(-1);

        // Local address for the TCP socket (use "" for any address)
        string localAddress = default("");

        // Address of the HyperFlowSynchronizer to connect to
        string connectAddressHyperFlowSynchronizer = default("HyperFlowSynchronizer");

        // Port of the HyperFlowSynchronizer to connect to
        int connectPortHyperFlowSynchronizer = default(1003);

        // When to initiate the connection to the HyperFlowSynchronizer
        double connectAt @unit("s") = default(1s);

        // How often to send ReportIn messages (should be 1/3 of the checkAliveEvery)
        // ReportIn messages inform the synchronizer about this controller and its switches
        double reportInEvery @unit("s") = default(1s);

        // How often to send SyncRequest messages to get updates from other controllers
        double checkSyncEvery @unit("s") = default(1s);

        // How often to check if other controllers are alive
        // Should be the same as aliveInterval of the synchronizer module
        double checkAliveEvery @unit("s") = default(3s);
}
