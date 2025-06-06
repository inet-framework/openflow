

package openflow.nodes;

import inet.common.misc.ThruputMeteringChannel;
import inet.node.ethernet.EthernetSwitch;
import inet.node.inet.StandardHost;
import openflow.openflow.switch.Open_Flow_Switch;


//
// OpenFlow domain consisting of an OpenFlow switch and several hosts, but NO controller.
//
module Open_Flow_Domain
{
    parameters:
        @display("bgb=347,267;i=misc/cloud;is=vs;bgl=2");
        int numClients = default(0);
        int domainID = default(-1);

    gates:
        inout gateDPlane[] @labels(DataPlane-conn);
        inout gateCPlane[] @labels(ControlPlane-conn);
    types:
        channel ethernetline extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 100Mbps;
            thruputDisplayFormat = "u";
        }
    submodules:
        open_flow_switch: Open_Flow_Switch {
            @display("p=120,186");
        }

        etherSwitch: EthernetSwitch {
            @display("p=240,186");
        }

        client[this.numClients]: StandardHost {
            @display("p=120,50,row,90");
        }
    connections allowunconnected:
        for i=0..sizeof(gateDPlane)-1 {
            gateDPlane[i] <--> open_flow_switch.gateDataPlane++;
        }

        for i=0..numClients-1 {
            client[i].ethg++ <--> ethernetline <--> open_flow_switch.gateDataPlane++;
        }

        for i=0..sizeof(gateCPlane)-1 {
            etherSwitch.ethg++ <--> gateCPlane[i];
        }

        etherSwitch.ethg++ <--> ethernetline <--> open_flow_switch.gateControlPlane++;
}

