

package openflow.networks;

import inet.nodes.ethernet.EtherSwitch;
import inet.nodes.inet.Router;
import inet.nodes.inet.StandardHost;
import inet.util.ThruputMeteringChannel;
import inet.networklayer.autorouting.ipv4.*;

import openflow.utility.*;
import openflow.nodes.*;
import openflow.openflow.controller.*;
import openflow.openflow.switch.*;

network Scenario_DynamicFatTree
{
    @display("bgb=842,642;");


    types:
        channel backboneline extends ThruputMeteringChannel
        {
            delay = 1us;
            datarate = 40Gbps;
            thruputDisplayFormat = "u";
        }
    submodules:

        spanningTree: StaticSpanningTree {
            @display("p=458,190");
        }

        openFlowGraphAnalyzer: OpenFlowGraphAnalyzer {
            @display("p=458,270");
        }


        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=198,190");
        }
        open_flow_controller1: Open_Flow_Controller {
            @display("p=322,190");
        }

        fat_tree: DynamicFatTree {
            @display("p=322,367;is=vl");
        }



    connections allowunconnected:

        fat_tree.gateCPlane++ <--> backboneline <--> open_flow_controller1.ethg++;
}
