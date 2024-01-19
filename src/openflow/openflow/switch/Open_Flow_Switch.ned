

package openflow.openflow.switch;

import inet.linklayer.contract.IWiredNic;
import inet.linklayer.ethernet.EthernetInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.contract.INetworkLayer;
import inet.networklayer.contract.IRoutingTable;
import inet.transportlayer.contract.ITCP;


module Open_Flow_Switch
{
    parameters:
        @networkNode();
        @OF_Switch();
        @labels(node,ethernet-node);
        @display("i=device/switch;i2=openflow/OpenFlow-Logo-small");
        bool sendCompletePacket = default(false);
        double serviceTime @unit("s") = default(0s);
        bool csmacdSupport = default(true);  // by default use CSMA/CD
        string macType = default(csmacdSupport ? "EtherMAC" : "EtherMACFullDuplex"); // ~EtherMAC or ~EtherMACFullDuplex

        string networkLayerType = default("IPv4NetworkLayer");
        string routingTableType = default("IPv4RoutingTable");

        //submodules
        string tcpType = default("TCP");  // tcp implementation (e.g. TCP, TCP_old, TCP_NSC)
        bool forwarding = default(false);
        bool multicastForwarding = default(false);
        string routingFile = default("");

        routingTable.forwarding = this.forwarding;
        routingTable.multicastForwarding = this.multicastForwarding;   // for IPv4, IPv6, Generic
        *.routingTableModule = default(absPath(".routingTable"));
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        etherMAC[*].encapType = default("EtherEncapDummy");
        etherMAC[*].csmacdSupport = this.csmacdSupport;
        etherMAC[*].macType = this.macType;
        networkLayer.proxyARP = default(false); 

    gates:
        inout gateControlPlane[] @labels(ControlPlane);
        inout gateDataPlane[] @labels(DataPlane);

    submodules:

        interfaceTable: InterfaceTable {
            parameters:
                @display("p=446,203");
        }
        tcp: <tcpType> like ITCP {
            parameters:
                @display("p=315,90");
        }
        routingTable: <routingTableType> like IRoutingTable if routingTableType != "" {
            parameters:
                @display("p=200,203");
        }
        networkLayer: <networkLayerType> like INetworkLayer {
            parameters:
                @display("p=200,90;q=queue");
            gates:
                ifIn[sizeof(parent.gateControlPlane)];
                ifOut[sizeof(parent.gateControlPlane)];
        }
        eth[sizeof(this.gateControlPlane)]: EthernetInterface {
            parameters:
                @display("p=75,90,row,90;q=txQueue");
        }
        etherMAC[sizeof(gateDataPlane)]: <default("EthernetInterface")> like IWiredNic {
            parameters:
                mac.promiscuous = default(true);
                @display("p=633,90,c,70");
        }

        OF_Switch: OF_Switch {
            @display("p=446,90");
            sendCompletePacket = parent.sendCompletePacket;
            gates:
                dataPlaneOut[sizeof(parent.gateDataPlane)];
                dataPlaneIn[sizeof(parent.gateDataPlane)];
        }

    connections allowunconnected:
        for i=0..sizeof(this.gateControlPlane)-1 {
            eth[i].phys <--> gateControlPlane[i];
            eth[i].upperLayerOut --> networkLayer.ifIn[i];
            eth[i].upperLayerIn <-- networkLayer.ifOut[i];
        }

        for i=0..sizeof(gateDataPlane)-1 {
            etherMAC[i].phys <--> gateDataPlane[i];
            OF_Switch.dataPlaneOut[i] --> etherMAC[i].upperLayerIn;
            etherMAC[i].upperLayerOut --> OF_Switch.dataPlaneIn[i];
        }
        tcp.ipOut --> networkLayer.transportIn++;
        tcp.ipIn <-- networkLayer.transportOut++;

        tcp.appOut++ --> OF_Switch.controlPlaneIn;
        OF_Switch.controlPlaneOut --> tcp.appIn++;


}
