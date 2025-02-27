
package openflow.hyperflow;
import openflow.controllerApps.IControllerApp;

//
// [GENERATED DOCUMENTATION -- ACCURACY UNVERIFIED]
// The HF_ARPResponder is a specialized controller application that extends the basic ARPResponder
// functionality to work within the HyperFlow distributed controller architecture. (The HF prefix
// stands for HyperFlow.)
//
// Basic ARPResponder Functionality:
// - Maintains a mapping between IP addresses and MAC addresses
// - Responds to ARP requests if it knows the MAC address for the requested IP
// - Floods ARP requests to all switches if it doesn't know the requested MAC address
// - Learns new IP-to-MAC mappings from ARP packets passing through the network
//
// HyperFlow is a distributed controller architecture that:
// - Enables multiple OpenFlow controllers to work together as a logically centralized controller
// - Provides fault tolerance and scalability through controller distribution
// - Synchronizes state between controllers using a publish-subscribe mechanism
// - Allows controllers to operate independently while maintaining a consistent network view
//
// HF_ARPResponder's Role:
//
// 1. State Synchronization: When it learns a new IP-to-MAC mapping, it not only stores it locally
//    but also publishes this information to other controllers through the HyperFlow synchronization channel.
//
// 2. Distributed Learning: It can receive IP-to-MAC mappings discovered by other controllers through
//    the HyperFlow "ReFire" mechanism, allowing all controllers to maintain a consistent ARP table.
//
// 3. Fault Tolerance: If one controller fails, others can continue to respond to ARP requests
//    because they share the same ARP table information.
//
// 4. Scalability: By distributing the ARP handling across multiple controllers, the system can
//    handle larger networks more efficiently.
//
// Note: HF_ARPResponder requires the HyperFlowAgent to be installed in the same controller.
// The HyperFlowAgent provides the communication infrastructure that enables the
// distributed functionality of HF_ARPResponder.
//
simple HF_ARPResponder like IControllerApp
{
    parameters:
        @class(openflow::HF_ARPResponder);
        @signal[HyperFlowReFire];
        @display("i=block/app");
         int priority = default(1);
}
