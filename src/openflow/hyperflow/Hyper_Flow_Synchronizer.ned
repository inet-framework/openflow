

package openflow.hyperflow;
import inet.linklayer.ethernet.EthernetInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.contract.INetworkLayer;
import inet.networklayer.contract.IRoutingTable;
import inet.transportlayer.contract.ITCP;


//
// TODO documentation
//
module Hyper_Flow_Synchronizer
{
    parameters:
        @networkNode();
        @labels(node,ethernet-node);
        @display("i=device/server;bgb=582,213;i2=openflow/OpenFlow-Logo-small");

		//submodules
        string tcpType = default("TCP");  // tcp implementation (e.g. TCP, TCP_old, TCP_NSC)
        int numExtInterfaces = default(0);
        double serviceTime @unit("s") = default(0s);

        string networkLayerType = default("IPv4NetworkLayer");
        string routingTableType = default("IPv4RoutingTable");

        bool forwarding = default(false);
        bool multicastForwarding = default(false);
        string routingFile = default("");

        routingTable.forwarding = forwarding;
        routingTable.multicastForwarding = multicastForwarding;   // for IPv4, IPv6, Generic
        *.routingTableModule = default(absPath(".routingTable"));
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        int priority = default(0);
 
    gates:
        inout ethg[] @labels(EtherFrame-conn);

    submodules:
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=422,35");
        }
        tcp: <tcpType> like ITCP {
            parameters:
                @display("p=246,138");
        }
        routingTable: <routingTableType> like IRoutingTable if routingTableType != "" {
            parameters:
                @display("p=53,250;is=s");
        }
        networkLayer: <networkLayerType> like INetworkLayer {
            parameters:
                @display("p=355,278;q=queue");
            gates:
                ifIn[sizeof(ethg)];
                ifOut[sizeof(ethg)];
        }
        eth[sizeof(ethg)]: EthernetInterface {
            parameters:
                @display("p=432,138,row,90;q=txQueue");
        }
        HyperFlowSynchronizer: HyperFlowSynchronizer {
            @display("p=89,138");
        }
    connections allowunconnected:
        tcp.ipOut --> networkLayer.transportIn++;
        tcp.ipIn <-- networkLayer.transportOut++;

        for i=0..sizeof(ethg)-1 {
            ethg[i] <--> eth[i].phys;
            eth[i].upperLayerOut --> networkLayer.ifIn[i];
            eth[i].upperLayerIn <-- networkLayer.ifOut[i];
        }

        tcp.appOut++ --> HyperFlowSynchronizer.tcpIn;
        HyperFlowSynchronizer.tcpOut --> tcp.appIn++;
}


