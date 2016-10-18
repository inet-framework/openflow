

package openflow.openflow.switch;

import inet.applications.pingapp.PingApp;
import inet.applications.ITCPApp;
import inet.base.NotificationBoard;
import inet.linklayer.ethernet.EtherMAC;
import inet.linklayer.ethernet.EthernetInterface;
import inet.linklayer.ext.ExtInterface;
import inet.linklayer.ppp.PPPInterface;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.ipv4.RoutingTable;
import inet.transport.ITCP;
import inet.transport.udp.UDP;
import inet.util.TCPDump;
import inet.nodes.inet.NetworkLayer;
import inet.linklayer.IWiredNic;
import inet.linklayer.configurator.L2NodeConfigurator;



module Open_Flow_Switch
{
    parameters:
        @node();
        @OF_Switch();
        @labels(node,ethernet-node);
        @display("i=device/switch;i2=openflow/OpenFlow-Logo-small;bgb=757,314");
        bool sendCompletePacket = default(false);
        double serviceTime @unit("s") = default(0s);
        bool csmacdSupport = default(true);  // by default use CSMA/CD
        string macType = default(csmacdSupport ? "EtherMAC" : "EtherMACFullDuplex"); // ~EtherMAC or ~EtherMACFullDuplex

        //submodules
        string tcpType = default("TCP");  // tcp implementation (e.g. TCP, TCP_old, TCP_NSC)
        bool IPForward = default(false);
        string routingFile = default("");

        etherMAC[*].encapType = "EtherEncapDummy";
        etherMAC[*].csmacdSupport = csmacdSupport;
        etherMAC[*].macType = macType;

    gates:
        inout gateControlPlane[] @labels(ControlPlane);
        inout gateDataPlane[] @labels(DataPlane);

    submodules:


        notificationBoard: NotificationBoard {
            parameters:
                @display("p=263,246");
        }
        interfaceTable: InterfaceTable {
            parameters:
                @display("p=363,246");
        }
        routingTable: RoutingTable {
            parameters:
                IPForward = IPForward;
                routerId = "";
                routingFile = routingFile;
                @display("p=464,246");
        }
        tcp: <tcpType> like ITCP {
            parameters:
                @display("p=333,123");
        }
        networkLayer: NetworkLayer {
            parameters:
                proxyARP = false;
                @display("p=236,123;q=queue");
            gates:
                ifIn[sizeof(gateControlPlane)];
                ifOut[sizeof(gateControlPlane)];
        }
        eth[sizeof(gateControlPlane)]: EthernetInterface {
            parameters:
                @display("p=93,123,row,90;q=txQueue");
        }
        etherMAC[sizeof(gateDataPlane)]: <default("EthernetInterface")> like IWiredNic {
            parameters:
                mac.promiscuous = true;
                @display("p=651,123");
        }

        OF_Switch: OF_Switch {
            @display("p=464,123");
            sendCompletePacket = sendCompletePacket;
            gates:
                dataPlaneOut[sizeof(gateDataPlane)];
                dataPlaneIn[sizeof(gateDataPlane)];
        }

    connections allowunconnected:
        for i=0..sizeof(gateControlPlane)-1 {
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
