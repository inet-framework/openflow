
package openflow.nodes;

import inet.common.misc.ThruputMeteringChannel;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.StandardHost;
import openflow.openflow.switch.Open_Flow_Switch;


//
// OpenFlow domain consisting of an OpenFlow switch and several hosts, but NO controller.
//
module DynamicFatTree
{
    parameters:
        @display("bgb=2277,571;i=misc/cloud;is=vs;bgl=2");
        int K = default(4);

        int podNum = K;                      // Pod number in FatTree
        int coreSwitchNum = pow((K/2),2);    // Core switches 
        int aggrSwitchNum = ((K/2)*K);       // Aggregation switches
        int edgeSwitchNum = ((K/2)*K);       // Edge switches
        int hostNum = (K*pow((K/2),2));      // Hosts in K-ary FatTree

    gates:
        inout gateCPlane[] @labels(ControlPlane-conn);

    types:
        channel ethernetline extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }
    submodules:

        coreLayerSwitches[coreSwitchNum]: Open_Flow_Switch {
            @display("p=306,55,row,90");
        }

        aggLayerSwitches[aggrSwitchNum]: Open_Flow_Switch {
            @display("p=306,200,row,90");
        }

        edgeLayerSwitches[edgeSwitchNum]: Open_Flow_Switch {
            @display("p=306,306,row,90");
        }

        etherSwitch: EtherSwitch {
            @display("p=79,250");
        }

        client[hostNum]: StandardHost {
            @display("p=306,434,row,90");
        }

    connections allowunconnected:

        for pod=0..podNum-1, for aggr=0..(aggrSwitchNum/podNum)-1, for x=((K/2)*aggr)..((K/2)*(aggr+1))-1 {
            aggLayerSwitches[aggr+pod*(aggrSwitchNum/podNum)].gateDataPlane++ <--> ethernetline <--> coreLayerSwitches[x].gateDataPlane++;
        }

        for pod=0..podNum-1, for edge=0..(edgeSwitchNum/podNum)-1, for x=(edgeSwitchNum/podNum)*pod..((edgeSwitchNum/podNum)*(pod+1))-1 {
            edgeLayerSwitches[edge+pod*(edgeSwitchNum/podNum)].gateDataPlane++ <--> ethernetline <--> aggLayerSwitches[x].gateDataPlane++;
        }

        for pod=0..podNum-1, for edge=0..(edgeSwitchNum/podNum)-1, for x=0..(hostNum/podNum/(edgeSwitchNum/podNum))-1 {
            edgeLayerSwitches[edge+pod*(edgeSwitchNum/podNum)].gateDataPlane++ <--> ethernetline <--> client[x+(edge+(pod*(edgeSwitchNum/podNum)))*(hostNum/podNum/(edgeSwitchNum/podNum))].ethg++;
        }


        //cplane
        for i=0..(coreSwitchNum)-1 {
            coreLayerSwitches[i].gateControlPlane++ <--> ethernetline <--> etherSwitch.ethg++;
        }
        for i=0..(aggrSwitchNum)-1 {
            aggLayerSwitches[i].gateControlPlane++ <--> ethernetline <--> etherSwitch.ethg++;
        }
        for i=0..(edgeSwitchNum)-1 {
            edgeLayerSwitches[i].gateControlPlane++ <--> ethernetline <--> etherSwitch.ethg++;
        }

        for i=0..sizeof(gateCPlane)-1 {
            gateCPlane[i] <--> etherSwitch.ethg++;
        }

}

