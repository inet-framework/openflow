
package openflow.nodes;

import inet.common.misc.ThruputMeteringChannel;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;
import openflow.openflow.switch.Open_Flow_Switch;
import inet.node.ethernet.Eth100M;

//
// OpenFlow domain consisting of an OpenFlow switch and several hosts, but NO controller.
//
module DynamicFatTree
{
    parameters:
        @display("bgb=2277,571;i=misc/cloud;is=vs;bgl=2");
        int K = default(4);

        int podNum = K;                      // Pod number in FatTree
        int coreSwitchNum = int(pow((K/2),2));    // Core switches 
        int aggrSwitchNum = int((K/2)*K);       // Aggregation switches
        int edgeSwitchNum = int((K/2)*K);       // Edge switches
        int hostNum = int(K*pow((K/2),2));      // Hosts in K-ary FatTree

    gates:
        inout gateCPlane[] @labels(ControlPlane-conn);

    types:
        channel ethernetline extends Eth100M
        {
            length = default(200m); //delay = 1us;
            //datarate = 100Mbps;
            //thruputDisplayFormat = "u";
        }

    submodules:

        coreLayerSwitches[coreSwitchNum]: Open_Flow_Switch {
            @display("p=306,55,row,90");
        }

        aggLayerSwitches[aggrSwitchNum]: Open_Flow_Switch {
            @display("p=522,200,row,90");
        }

        edgeLayerSwitches[edgeSwitchNum]: Open_Flow_Switch {
            @display("p=345,393,row,90");
        }

        etherSwitch: EthernetSwitch {
            @display("p=79,250");
        }

        client[hostNum]: StandardHost {
            @display("p=182,470,row,90");
        }

    connections allowunconnected:

        for pod=0..podNum-1, for aggr=0..int((aggrSwitchNum/podNum))-1, for x=int(((K/2)*aggr))..int(((K/2)*(aggr+1))-1) {
            aggLayerSwitches[int(aggr+pod*(aggrSwitchNum/podNum))].gateDataPlane++ <--> ethernetline { length = 200m + pod*1m + aggr*0.1m + x*0.01m; } <--> coreLayerSwitches[x].gateDataPlane++;
        }

        for pod=0..podNum-1, for edge=0..int((edgeSwitchNum/podNum)-1), for x=int((edgeSwitchNum/podNum)*pod)..int(((edgeSwitchNum/podNum)*(pod+1))-1) {
            edgeLayerSwitches[int(edge+pod*(edgeSwitchNum/podNum))].gateDataPlane++ <--> ethernetline { length = 210m + pod*1m + edge*0.1m + x*1m; } <--> aggLayerSwitches[x].gateDataPlane++;
        }

        for pod=0..podNum-1, for edge=0..int((edgeSwitchNum/podNum)-1), for x=0..int((hostNum/podNum/(edgeSwitchNum/podNum))-1) {
            edgeLayerSwitches[int(edge+pod*(edgeSwitchNum/podNum))].gateDataPlane++ <--> ethernetline { length = 220m + pod*1m + edge*0.1m + x*1m; } <--> client[int(x+(edge+(pod*(edgeSwitchNum/podNum)))*(hostNum/podNum/(edgeSwitchNum/podNum)))].ethg++;
        }


        //cplane
        for i=0..(coreSwitchNum)-1 {
            coreLayerSwitches[i].gateControlPlane++ <--> ethernetline { length = 200m + i*1m; } <--> etherSwitch.ethg++;
        }
        for i=0..(aggrSwitchNum)-1 {
            aggLayerSwitches[i].gateControlPlane++ <--> ethernetline { length = 200.1m + i*1m; } <--> etherSwitch.ethg++;
        }
        for i=0..(edgeSwitchNum)-1 {
            edgeLayerSwitches[i].gateControlPlane++ <--> ethernetline { length = 200.2m + i*1m; } <--> etherSwitch.ethg++;
        }

        for i=0..sizeof(gateCPlane)-1 {
            gateCPlane[i] <--> etherSwitch.ethg++;
        }
}
