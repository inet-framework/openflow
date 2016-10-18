

package openflow.hyperflow;
import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EthernetInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.nodes.inet.NetworkLayer;
import inet.transport.ITCP;
import inet.applications.ITCPApp;

//
// TODO documentation
//
module Hyper_Flow_Synchronizer
{
    parameters:
        @node();
        @labels(node,ethernet-node);
        @display("i=device/server;bgb=582,213;i2=openflow/OpenFlow-Logo-small");

		//submodules
        string tcpType = default("TCP");  // tcp implementation (e.g. TCP, TCP_old, TCP_NSC)
        bool IPForward = default(false);
        string routingFile = default("");
        int numExtInterfaces = default(0);
        double serviceTime @unit("s") = default(0s);



    gates:
        inout ethg[] @labels(EtherFrame-conn);
    submodules:


        notificationBoard: NotificationBoard {
            parameters:
                @display("p=236,35");
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=422,35");
        }
        routingTable: RoutingTable {
            parameters:
                IPForward = IPForward;
                routerId = "";
                routingFile = routingFile;
                @display("p=333,35");
        }
        tcp: <tcpType> like ITCP {
            parameters:
                @display("p=246,138");
        }
        networkLayer: NetworkLayer {
            parameters:
                proxyARP = false;
                @display("p=333,138;q=queue");
            gates:
                ifIn[sizeof(pppg)+sizeof(ethg)+numExtInterfaces];
                ifOut[sizeof(pppg)+sizeof(ethg)+numExtInterfaces];
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


