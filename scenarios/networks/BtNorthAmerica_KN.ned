//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package openflow.scenarios.networks;

import inet.common.misc.ThruputMeteringChannel;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import openflow.nodes.DistanceChannel;
import openflow.nodes.Open_Flow_Domain;
import openflow.openflow.controller.Open_Flow_Controller;
import openflow.utility.ControllerInvolvementFilter;
import openflow.utility.OpenFlowGraphAnalyzer;
import openflow.utility.StaticSpanningTree;


network Scenario_BtNorthAmerica_KN
{
    parameters:
        int numControllers = default(1);
        int placementID = default(1);
    types:
        channel backboneline extends ThruputMeteringChannel
        {
            delay = default(1us);
            datarate = 40Gbps;
            thruputDisplayFormat = "u";
        }
    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=449,598");
        }

        controllerInvolvementFilter: ControllerInvolvementFilter {
            @display("p=59,39");
        }
        spanningTree: StaticSpanningTree {
            @display("p=349,598");
        }

        openFlowGraphAnalyzer: OpenFlowGraphAnalyzer {
            @display("p=218,598");
        }

        root: Open_Flow_Controller {
            @display("p=396,23");
        }
        open_flow_controller1: Open_Flow_Controller if numControllers >=1 {
            @display("p=20,100");
        }
        open_flow_controller2: Open_Flow_Controller if numControllers >=2 {
            @display("p=40,100");
        }
        open_flow_controller3: Open_Flow_Controller if numControllers >=3 {
            @display("p=60,100");
        }
        open_flow_controller4: Open_Flow_Controller if numControllers >=4 {
            @display("p=80,100");
        }
        open_flow_controller5: Open_Flow_Controller if numControllers >=5 {
            @display("p=100,100");
        }
        ofs_1: Open_Flow_Domain {
            @display("p=225,174");
        }
        ofs_2: Open_Flow_Domain {
            @display("p=138,183");
        }
        ofs_3: Open_Flow_Domain {
            @display("p=223,209");
        }
        ofs_4: Open_Flow_Domain {
            @display("p=5,59");
        }
        ofs_5: Open_Flow_Domain {
            @display("p=0,99");
        }
        ofs_6: Open_Flow_Domain {
            @display("p=70,0");
        }
        ofs_7: Open_Flow_Domain {
            @display("p=9,1");
        }
        ofs_8: Open_Flow_Domain {
            @display("p=59,341");
        }
        ofs_9: Open_Flow_Domain {
            @display("p=60,344");
        }
        ofs_10: Open_Flow_Domain {
            @display("p=602,184");
        }
        ofs_11: Open_Flow_Domain {
            @display("p=604,185");
        }
        ofs_12: Open_Flow_Domain {
            @display("p=640,143");
        }
        ofs_13: Open_Flow_Domain {
            @display("p=567,229");
        }
        ofs_14: Open_Flow_Domain {
            @display("p=10,5");
        }
        ofs_15: Open_Flow_Domain {
            @display("p=566,230");
        }
        ofs_16: Open_Flow_Domain {
            @display("p=436,156");
        }
        ofs_17: Open_Flow_Domain {
            @display("p=323,373");
        }
        ofs_18: Open_Flow_Domain {
            @display("p=202,321");
        }
        ofs_19: Open_Flow_Domain {
            @display("p=150,386");
        }
        ofs_20: Open_Flow_Domain {
            @display("p=135,358");
        }
        ofs_21: Open_Flow_Domain {
            @display("p=436,156");
        }
        ofs_22: Open_Flow_Domain {
            @display("p=476,351");
        }
        ofs_23: Open_Flow_Domain {
            @display("p=500,480");
        }
        ofs_24: Open_Flow_Domain {
            @display("p=341,441");
        }
        ofs_25: Open_Flow_Domain {
            @display("p=350,224");
        }
        ofs_26: Open_Flow_Domain {
            @display("p=13,267");
        }
        ofs_27: Open_Flow_Domain {
            @display("p=85,110");
        }
        ofs_28: Open_Flow_Domain {
            @display("p=136,30");
        }
        ofs_29: Open_Flow_Domain {
            @display("p=179,52");
        }
        ofs_30: Open_Flow_Domain {
            @display("p=323,22");
        }
        ofs_31: Open_Flow_Domain {
            @display("p=367,74");
        }
        ofs_32: Open_Flow_Domain {
            @display("p=328,139");
        }
        ofs_33: Open_Flow_Domain {
            @display("p=334,171");
        }
    connections allowunconnected:

        ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 595km; } <--> ofs_2.gateDPlane++;
        ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 595km; } <--> ofs_2.gateCPlane++;
        ofs_1.gateDPlane++ <--> DistanceChannel {  distance = 156km; } <--> ofs_3.gateDPlane++;
        ofs_1.gateCPlane++ <--> DistanceChannel {  distance = 156km; } <--> ofs_3.gateCPlane++;
        ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 597km; } <--> ofs_3.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 884km; } <--> ofs_6.gateDPlane++;
        ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 884km; } <--> ofs_6.gateCPlane++;
        ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 925km; } <--> ofs_8.gateDPlane++;
        ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 925km; } <--> ofs_8.gateCPlane++;
        ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 2022km; } <--> ofs_21.gateDPlane++;
        ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 2022km; } <--> ofs_21.gateCPlane++;
        ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 953km; } <--> ofs_26.gateDPlane++;
        ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 953km; } <--> ofs_26.gateCPlane++;
        ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 476km; } <--> ofs_27.gateDPlane++;
        ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 476km; } <--> ofs_27.gateCPlane++;
        ofs_2.gateDPlane++ <--> DistanceChannel {  distance = 622km; } <--> ofs_29.gateDPlane++;
        ofs_2.gateCPlane++ <--> DistanceChannel {  distance = 622km; } <--> ofs_29.gateCPlane++;
        ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 538km; } <--> ofs_18.gateDPlane++;
        ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 538km; } <--> ofs_18.gateCPlane++;
        ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 943km; } <--> ofs_20.gateDPlane++;
        ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 943km; } <--> ofs_20.gateCPlane++;
        ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 892km; } <--> ofs_25.gateDPlane++;
        ofs_3.gateCPlane++ <--> DistanceChannel {  distance = 892km; } <--> ofs_25.gateCPlane++;
        ofs_3.gateDPlane++ <--> DistanceChannel {  distance = 1504km; } <--> ofs_26.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 167km; } <--> ofs_5.gateDPlane++;
        ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 167km; } <--> ofs_5.gateCPlane++;
        ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 1315km; } <--> ofs_8.gateDPlane++;
        ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 1315km; } <--> ofs_8.gateCPlane++;
        ofs_4.gateDPlane++ <--> DistanceChannel {  distance = 219km; } <--> ofs_14.gateDPlane++;
        ofs_4.gateCPlane++ <--> DistanceChannel {  distance = 219km; } <--> ofs_14.gateCPlane++;
        ofs_5.gateDPlane++ <--> DistanceChannel {  distance = 386km; } <--> ofs_14.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_6.gateDPlane++ <--> DistanceChannel {  distance = 368km; } <--> ofs_7.gateDPlane++;
        ofs_6.gateCPlane++ <--> DistanceChannel {  distance = 368km; } <--> ofs_7.gateCPlane++;
        ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 16km; } <--> ofs_14.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 2789km; } <--> ofs_16.gateDPlane++;
        ofs_7.gateCPlane++ <--> DistanceChannel {  distance = 2789km; } <--> ofs_16.gateCPlane++;
        ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 1794km; } <--> ofs_20.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_7.gateDPlane++ <--> DistanceChannel {  distance = 787km; } <--> ofs_28.gateDPlane++;
        ofs_7.gateCPlane++ <--> DistanceChannel {  distance = 787km; } <--> ofs_28.gateCPlane++;
        ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 16km; } <--> ofs_9.gateDPlane++;
        ofs_8.gateCPlane++ <--> DistanceChannel {  distance = 16km; } <--> ofs_9.gateCPlane++;
        ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 582km; } <--> ofs_20.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 2214km; } <--> ofs_24.gateDPlane++;
        ofs_8.gateCPlane++ <--> DistanceChannel {  distance = 2214km; } <--> ofs_24.gateCPlane++;
        ofs_8.gateDPlane++ <--> DistanceChannel {  distance = 489km; } <--> ofs_26.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 2207km; } <--> ofs_24.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_9.gateDPlane++ <--> DistanceChannel {  distance = 503km; } <--> ofs_26.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 14km; } <--> ofs_11.gateDPlane++;
        ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 14km; } <--> ofs_11.gateCPlane++;
        ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 316km; } <--> ofs_12.gateDPlane++;
        ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 316km; } <--> ofs_12.gateCPlane++;
        ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 316km; } <--> ofs_13.gateDPlane++;
        ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 316km; } <--> ofs_13.gateCPlane++;
        ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 1132km; } <--> ofs_16.gateDPlane++;
        ofs_10.gateCPlane++ <--> DistanceChannel {  distance = 1132km; } <--> ofs_16.gateCPlane++;
        ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 2269km; } <--> ofs_24.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_10.gateDPlane++ <--> DistanceChannel {  distance = 1750km; } <--> ofs_25.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 306km; } <--> ofs_12.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 325km; } <--> ofs_13.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 328km; } <--> ofs_15.gateDPlane++;
        ofs_11.gateCPlane++ <--> DistanceChannel {  distance = 328km; } <--> ofs_15.gateCPlane++;
        ofs_11.gateDPlane++ <--> DistanceChannel {  distance = 1146km; } <--> ofs_16.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 3km; } <--> ofs_15.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 958km; } <--> ofs_21.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 875km; } <--> ofs_22.gateDPlane++;
        ofs_13.gateCPlane++ <--> DistanceChannel {  distance = 875km; } <--> ofs_22.gateCPlane++;
        ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 1319km; } <--> ofs_23.gateDPlane++;
        ofs_13.gateCPlane++ <--> DistanceChannel {  distance = 1319km; } <--> ofs_23.gateCPlane++;
        ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 1963km; } <--> ofs_24.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 1520km; } <--> ofs_25.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_13.gateDPlane++ <--> DistanceChannel {  distance = 3901km; } <--> ofs_26.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_14.gateDPlane++ <--> DistanceChannel {  distance = 1124km; } <--> ofs_26.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_14.gateDPlane++ <--> DistanceChannel {  distance = 637km; } <--> ofs_27.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_15.gateDPlane++ <--> DistanceChannel {  distance = 956km; } <--> ofs_16.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_15.gateDPlane++ <--> DistanceChannel {  distance = 872km; } <--> ofs_22.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_16.gateDPlane++ <--> DistanceChannel {  distance = 0km; } <--> ofs_21.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_16.gateDPlane++ <--> DistanceChannel {  distance = 664km; } <--> ofs_25.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_16.gateDPlane++ <--> DistanceChannel {  distance = 2967km; } <--> ofs_26.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 1325km; } <--> ofs_19.gateDPlane++;
        ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 1325km; } <--> ofs_19.gateCPlane++;
        ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 363km; } <--> ofs_24.gateDPlane++;
        ofs_17.gateCPlane++ <--> DistanceChannel {  distance = 363km; } <--> ofs_24.gateCPlane++;
        ofs_17.gateDPlane++ <--> DistanceChannel {  distance = 731km; } <--> ofs_25.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_18.gateDPlane++ <--> DistanceChannel {  distance = 508km; } <--> ofs_19.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_19.gateDPlane++ <--> DistanceChannel {  distance = 173km; } <--> ofs_20.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 945km; } <--> ofs_22.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 664km; } <--> ofs_25.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_21.gateDPlane++ <--> DistanceChannel {  distance = 571km; } <--> ofs_31.gateDPlane++;
        ofs_21.gateCPlane++ <--> DistanceChannel {  distance = 571km; } <--> ofs_31.gateCPlane++;
        ofs_22.gateDPlane++ <--> DistanceChannel {  distance = 671km; } <--> ofs_23.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_22.gateDPlane++ <--> DistanceChannel {  distance = 1128km; } <--> ofs_24.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_23.gateDPlane++ <--> DistanceChannel {  distance = 1272km; } <--> ofs_24.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_24.gateDPlane++ <--> DistanceChannel {  distance = 2601km; } <--> ofs_26.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_25.gateDPlane++ <--> DistanceChannel {  distance = 662km; } <--> ofs_31.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_25.gateDPlane++ <--> DistanceChannel {  distance = 263km; } <--> ofs_33.gateDPlane++;
        ofs_25.gateCPlane++ <--> DistanceChannel {  distance = 263km; } <--> ofs_33.gateCPlane++;
        ofs_28.gateDPlane++ <--> DistanceChannel {  distance = 287km; } <--> ofs_29.gateDPlane++;
        // this edge is not part of the MST, skipping
        ofs_30.gateDPlane++ <--> DistanceChannel {  distance = 345km; } <--> ofs_31.gateDPlane++;
        ofs_30.gateCPlane++ <--> DistanceChannel {  distance = 345km; } <--> ofs_31.gateCPlane++;
        ofs_30.gateDPlane++ <--> DistanceChannel {  distance = 488km; } <--> ofs_32.gateDPlane++;
        ofs_30.gateCPlane++ <--> DistanceChannel {  distance = 488km; } <--> ofs_32.gateCPlane++;
        ofs_32.gateDPlane++ <--> DistanceChannel {  distance = 143km; } <--> ofs_33.gateDPlane++;
        // this edge is not part of the MST, skipping
        // placement 1, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_1.gateCPlane++ <--> backboneline { delay = 1.001us; } <--> root.ethg++ if (numControllers == 2 && placementID == 1);
        ofs_1.gateCPlane++ <--> backboneline { delay = 1.002us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 1);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.003us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 1);
        // placement 2, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.004us; } <--> root.ethg++ if (numControllers == 2 && placementID == 2);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.005us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 2);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.006us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 2);
        // placement 3, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.007us; } <--> root.ethg++ if (numControllers == 2 && placementID == 3);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.008us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 3);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.009us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 3);
        // placement 4, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.010us; } <--> root.ethg++ if (numControllers == 2 && placementID == 4);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.011us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 4);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.012us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 4);
        // placement 5, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.013us; } <--> root.ethg++ if (numControllers == 2 && placementID == 5);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.014us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 5);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.015us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 5);
        // placement 6, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.016us; } <--> root.ethg++ if (numControllers == 2 && placementID == 6);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.017us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 6);
        ofs_31.gateCPlane++ <--> backboneline { delay = 1.018us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 6);
        // placement 7, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.019us; } <--> root.ethg++ if (numControllers == 2 && placementID == 7);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.020us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 7);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.0210us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 7);
        // placement 8, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.022us; } <--> root.ethg++ if (numControllers == 2 && placementID == 8);
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.023us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 8);
        ofs_9.gateCPlane++ <--> backboneline { delay = 1.024us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 8);
        // placement 9, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.025us; } <--> root.ethg++ if (numControllers == 2 && placementID == 9);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.026us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 9);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.027us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 9);
        // placement 10, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.028us; } <--> root.ethg++ if (numControllers == 2 && placementID == 10);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.029us; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 10);
        ofs_21.gateCPlane++ <--> backboneline { delay = 1.030us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 10);
        // placement 11, k = 2
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_32.gateCPlane++ <--> backboneline { delay = 1.031us; } <--> root.ethg++ if (numControllers == 2 && placementID == 11);
        ofs_32.gateCPlane++ <--> backboneline { delay = 1.032s; } <--> open_flow_controller1.ethg++ if (numControllers == 2 && placementID == 11);
        ofs_33.gateCPlane++ <--> backboneline { delay = 1.033us; } <--> open_flow_controller2.ethg++ if (numControllers == 2 && placementID == 11);
        // placement 12, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.034us; } <--> root.ethg++ if (numControllers == 3 && placementID == 12);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.035us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 12);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.036us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 12);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.037us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 12);
        // placement 13, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.038us; } <--> root.ethg++ if (numControllers == 3 && placementID == 13);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.039us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 13);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.040us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 13);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.041us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 13);
        // placement 14, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.042us; } <--> root.ethg++ if (numControllers == 3 && placementID == 14);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.043us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 14);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.044us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 14);
        ofs_17.gateCPlane++ <--> backboneline { delay = 1.045us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 14);
        // placement 15, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.046us; } <--> root.ethg++ if (numControllers == 3 && placementID == 15);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.047us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 15);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.048us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 15);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.049us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 15);
        // placement 16, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.050us; } <--> root.ethg++ if (numControllers == 3 && placementID == 16);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.051us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 16);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.052us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 16);
        ofs_17.gateCPlane++ <--> backboneline { delay = 1.053us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 16);
        // placement 17, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.054us; } <--> root.ethg++ if (numControllers == 3 && placementID == 17);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.055us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 17);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.056us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 17);
        ofs_17.gateCPlane++ <--> backboneline { delay = 1.057us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 17);
        // placement 18, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_17.gateCPlane++ <--> backboneline { delay = 1.058us; } <--> root.ethg++ if (numControllers == 3 && placementID == 18);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.059us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 18);
        ofs_17.gateCPlane++ <--> backboneline { delay = 1.060us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 18);
        ofs_22.gateCPlane++ <--> backboneline { delay = 1.061us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 18);
        // placement 19, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.062us; } <--> root.ethg++ if (numControllers == 3 && placementID == 19);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.063us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 19);
        ofs_4.gateCPlane++ <--> backboneline { delay = 1.064us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 19);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.065us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 19);
        // placement 20, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.066us; } <--> root.ethg++ if (numControllers == 3 && placementID == 20);
        ofs_4.gateCPlane++ <--> backboneline { delay = 1.067us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 20);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.068us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 20);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.069us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 20);
        // placement 21, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.070us; } <--> root.ethg++ if (numControllers == 3 && placementID == 21);
        ofs_6.gateCPlane++ <--> backboneline { delay = 1.071us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 21);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.072us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 21);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.073us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 21);
        // placement 22, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.074us; } <--> root.ethg++ if (numControllers == 3 && placementID == 22);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.075us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 22);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.076us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 22);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.077us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 22);
        // placement 23, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.078us; } <--> root.ethg++ if (numControllers == 3 && placementID == 23);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.079us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 23);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.080us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 23);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.081us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 23);
        // placement 24, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_11.gateCPlane++ <--> backboneline { delay = 1.082us; } <--> root.ethg++ if (numControllers == 3 && placementID == 24);
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.083us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 24);
        ofs_11.gateCPlane++ <--> backboneline { delay = 1.084us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 24);
        ofs_12.gateCPlane++ <--> backboneline { delay = 1.085us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 24);
        // placement 25, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.086us; } <--> root.ethg++ if (numControllers == 3 && placementID == 25);
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.087us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 25);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.088us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 25);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.089us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 25);
        // placement 26, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.090us; } <--> root.ethg++ if (numControllers == 3 && placementID == 26);
        ofs_11.gateCPlane++ <--> backboneline { delay = 1.091us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 26);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.092us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 26);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.093us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 26);
        // placement 27, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.094us; } <--> root.ethg++ if (numControllers == 3 && placementID == 27);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.095us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 27);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.096us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 27);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.097us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 27);
        // placement 28, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_18.gateCPlane++ <--> backboneline { delay = 1.098us; } <--> root.ethg++ if (numControllers == 3 && placementID == 28);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.099us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 28);
        ofs_18.gateCPlane++ <--> backboneline { delay = 1.100us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 28);
        ofs_19.gateCPlane++ <--> backboneline { delay = 1.101us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 28);
        // placement 29, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_18.gateCPlane++ <--> backboneline { delay = 1.102us; } <--> root.ethg++ if (numControllers == 3 && placementID == 29);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.103us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 29);
        ofs_18.gateCPlane++ <--> backboneline { delay = 1.104us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 29);
        ofs_20.gateCPlane++ <--> backboneline { delay = 1.105us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 29);
        // placement 30, k = 3
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.106us; } <--> root.ethg++ if (numControllers == 3 && placementID == 30);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.107us; } <--> open_flow_controller1.ethg++ if (numControllers == 3 && placementID == 30);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.108us; } <--> open_flow_controller2.ethg++ if (numControllers == 3 && placementID == 30);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.109us; } <--> open_flow_controller3.ethg++ if (numControllers == 3 && placementID == 30);
        // placement 31, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.110us; } <--> root.ethg++ if (numControllers == 5 && placementID == 31);
        ofs_1.gateCPlane++ <--> backboneline { delay = 1.111us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 31);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.112us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 31);
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.113us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 31);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.114us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 31);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.115us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 31);
        // placement 32, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.116us; } <--> root.ethg++ if (numControllers == 5 && placementID == 32);
        ofs_1.gateCPlane++ <--> backboneline { delay = 1.117us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 32);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.118us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 32);
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.119us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 32);
        ofs_26.gateCPlane++ <--> backboneline { delay = 1.120us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 32);
        ofs_30.gateCPlane++ <--> backboneline { delay = 1.121us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 32);
        // placement 33, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.122us; } <--> root.ethg++ if (numControllers == 5 && placementID == 33);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.123us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 33);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.124us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 33);
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.125us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 33);
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.126us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 33);
        ofs_30.gateCPlane++ <--> backboneline { delay = 1.127us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 33);
        // placement 34, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.128us; } <--> root.ethg++ if (numControllers == 5 && placementID == 34);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.129us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 34);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.130us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 34);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.131us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 34);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.132us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 34);
        ofs_19.gateCPlane++ <--> backboneline { delay = 1.133us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 34);
        // placement 35, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.134us; } <--> root.ethg++ if (numControllers == 5 && placementID == 35);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.135us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 35);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.136us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 35);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.137us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 35);
        ofs_19.gateCPlane++ <--> backboneline { delay = 1.138us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 35);
        ofs_31.gateCPlane++ <--> backboneline { delay = 1.139us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 35);
        // placement 36, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.140us; } <--> root.ethg++ if (numControllers == 5 && placementID == 36);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.141us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 36);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.142us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 36);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.143us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 36);
        ofs_20.gateCPlane++ <--> backboneline { delay = 1.144us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 36);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.145us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 36);
        // placement 37, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.146us; } <--> root.ethg++ if (numControllers == 5 && placementID == 37);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.147us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 37);
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.148us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 37);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.149us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 37);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.150us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 37);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.151us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 37);
        // placement 38, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.152us; } <--> root.ethg++ if (numControllers == 5 && placementID == 38);
        ofs_2.gateCPlane++ <--> backboneline { delay = 1.153us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 38);
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.154us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 38);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.155us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 38);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.156us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 38);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.157us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 38);
        // placement 39, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.158us; } <--> root.ethg++ if (numControllers == 5 && placementID == 39);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.159us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 39);
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.160us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 39);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.161us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 39);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.162us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 39);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.163us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 39);
        // placement 40, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.164us; } <--> root.ethg++ if (numControllers == 5 && placementID == 40);
        ofs_3.gateCPlane++ <--> backboneline { delay = 1.165us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 40);
        ofs_8.gateCPlane++ <--> backboneline { delay = 1.166us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 40);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.167us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 40);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.168us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 40);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.169us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 40);
        // placement 41, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.170us; } <--> root.ethg++ if (numControllers == 5 && placementID == 41);
        ofs_4.gateCPlane++ <--> backboneline { delay = 1.171us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 41);
        ofs_5.gateCPlane++ <--> backboneline { delay = 1.172us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 41);
        ofs_6.gateCPlane++ <--> backboneline { delay = 1.173us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 41);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.174us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 41);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.175us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 41);
        // placement 42, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.176us; } <--> root.ethg++ if (numControllers == 5 && placementID == 42);
        ofs_4.gateCPlane++ <--> backboneline { delay = 1.177us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 42);
        ofs_5.gateCPlane++ <--> backboneline { delay = 1.178us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 42);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.179us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 42);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.180us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 42);
        ofs_27.gateCPlane++ <--> backboneline { delay = 1.181us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 42);
        // placement 43, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.182us; } <--> root.ethg++ if (numControllers == 5 && placementID == 43);
        ofs_4.gateCPlane++ <--> backboneline { delay = 1.183us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 43);
        ofs_5.gateCPlane++ <--> backboneline { delay = 1.184us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 43);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.185us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 43);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.186us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 43);
        ofs_28.gateCPlane++ <--> backboneline { delay = 1.187us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 43);
        // placement 44, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.188us; } <--> root.ethg++ if (numControllers == 5 && placementID == 44);
        ofs_4.gateCPlane++ <--> backboneline { delay = 1.189us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 44);
        ofs_6.gateCPlane++ <--> backboneline { delay = 1.190us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 44);
        ofs_7.gateCPlane++ <--> backboneline { delay = 1.191us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 44);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.192us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 44);
        ofs_27.gateCPlane++ <--> backboneline { delay = 1.193us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 44);
        // placement 45, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.194us; } <--> root.ethg++ if (numControllers == 5 && placementID == 45);
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.195us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 45);
        ofs_11.gateCPlane++ <--> backboneline { delay = 1.196us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 45);
        ofs_12.gateCPlane++ <--> backboneline { delay = 1.197us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 45);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.198us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 45);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.199us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 45);
        // placement 46, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.200us; } <--> root.ethg++ if (numControllers == 5 && placementID == 46);
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.201us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 46);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.202us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 46);
        ofs_20.gateCPlane++ <--> backboneline { delay = 1.203us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 46);
        ofs_22.gateCPlane++ <--> backboneline { delay = 1.204us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 46);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.205us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 46);
        // placement 47, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.206us; } <--> root.ethg++ if (numControllers == 5 && placementID == 47);
        ofs_10.gateCPlane++ <--> backboneline { delay = 1.207us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 47);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.208us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 47);
        ofs_20.gateCPlane++ <--> backboneline { delay = 1.209us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 47);
        ofs_22.gateCPlane++ <--> backboneline { delay = 1.210us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 47);
        ofs_33.gateCPlane++ <--> backboneline { delay = 1.211us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 47);
        // placement 48, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.212us; } <--> root.ethg++ if (numControllers == 5 && placementID == 48);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.213us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 48);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.214us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 48);
        ofs_20.gateCPlane++ <--> backboneline { delay = 1.215us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 48);
        ofs_22.gateCPlane++ <--> backboneline { delay = 1.216us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 48);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.217us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 48);
        // placement 49, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.218us; } <--> root.ethg++ if (numControllers == 5 && placementID == 49);
        ofs_13.gateCPlane++ <--> backboneline { delay = 1.219us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 49);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.220us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 49);
        ofs_20.gateCPlane++ <--> backboneline { delay = 1.221us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 49);
        ofs_22.gateCPlane++ <--> backboneline { delay = 1.222us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 49);
        ofs_33.gateCPlane++ <--> backboneline { delay = 1.223us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 49);
        // placement 50, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.224us; } <--> root.ethg++ if (numControllers == 5 && placementID == 50);
        ofs_14.gateCPlane++ <--> backboneline { delay = 1.225us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 50);
        ofs_15.gateCPlane++ <--> backboneline { delay = 1.226us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 50);
        ofs_20.gateCPlane++ <--> backboneline { delay = 1.227us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 50);
        ofs_22.gateCPlane++ <--> backboneline { delay = 1.228us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 50);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.229us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 50);
        // placement 51, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_31.gateCPlane++ <--> backboneline { delay = 1.230us; } <--> root.ethg++ if (numControllers == 5 && placementID == 51);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.231us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 51);
        ofs_21.gateCPlane++ <--> backboneline { delay = 1.232us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 51);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.233us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 51);
        ofs_30.gateCPlane++ <--> backboneline { delay = 1.234us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 51);
        ofs_31.gateCPlane++ <--> backboneline { delay = 1.235us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 51);
        // placement 52, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.236us; } <--> root.ethg++ if (numControllers == 5 && placementID == 52);
        ofs_16.gateCPlane++ <--> backboneline { delay = 1.237us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 52);
        ofs_21.gateCPlane++ <--> backboneline { delay = 1.238us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 52);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.239us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 52);
        ofs_31.gateCPlane++ <--> backboneline { delay = 1.240us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 52);
        ofs_33.gateCPlane++ <--> backboneline { delay = 1.241us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 52);
        // placement 53, k = 5
        // hfSyncHost according to minimum avg distance to ctrl
        ofs_32.gateCPlane++ <--> backboneline { delay = 1.242us; } <--> root.ethg++ if (numControllers == 5 && placementID == 53);
        ofs_25.gateCPlane++ <--> backboneline { delay = 1.243us; } <--> open_flow_controller1.ethg++ if (numControllers == 5 && placementID == 53);
        ofs_30.gateCPlane++ <--> backboneline { delay = 1.244us; } <--> open_flow_controller2.ethg++ if (numControllers == 5 && placementID == 53);
        ofs_31.gateCPlane++ <--> backboneline { delay = 1.245us; } <--> open_flow_controller3.ethg++ if (numControllers == 5 && placementID == 53);
        ofs_32.gateCPlane++ <--> backboneline { delay = 1.246us; } <--> open_flow_controller4.ethg++ if (numControllers == 5 && placementID == 53);
        ofs_33.gateCPlane++ <--> backboneline { delay = 1.247us; } <--> open_flow_controller5.ethg++ if (numControllers == 5 && placementID == 53);
}
