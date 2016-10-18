

package openflow.nodes;

import openflow.nodes.*;
import openflow.openflow.controller.*;
import openflow.openflow.switch.*;
import inet.nodes.inet.StandardHost;
import inet.util.ThruputMeteringChannel;
import inet.nodes.ethernet.EtherSwitch;
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
            gates:
                gateDataPlane[sizeof(gateDPlane)+numClients];
        }

        etherSwitch: EtherSwitch {
            @display("p=240,186");
            gates:
                ethg[sizeof(gateCPlane)];
        }

        client[numClients]: StandardHost {
            @display("p=120,50,row,90");
        }
    connections allowunconnected:
        for i=0..sizeof(gateDPlane)-1 {
            gateDPlane[i] <--> open_flow_switch.gateDataPlane[i];
        }

        for i=0..numClients-1 {
            client[i].ethg++ <--> ethernetline <--> open_flow_switch.gateDataPlane[sizeof(gateDPlane)+i];
        }

        for i=0..sizeof(gateCPlane)-1 {
            etherSwitch.ethg[i] <-->  gateCPlane[i];
        }

        etherSwitch.ethg++ <--> ethernetline <--> open_flow_switch.gateControlPlane++;
}

