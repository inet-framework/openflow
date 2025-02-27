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

package openflow.controllerApps;

//
// [GENERATED DOCUMENTATION -- ACCURACY UNVERIFIED]
// The LLDPAgent is a controller application responsible for network topology discovery
// using the Link Layer Discovery Protocol (LLDP). It is deployed exclusively on the
// controller side, not on switches.
//
// The module periodically sends LLDP packets to all switches using OpenFlow packet-out
// messages. Each switch forwards these LLDP packets on all its ports. When a switch
// receives an LLDP packet on one of its ports, it forwards it to the controller via
// a packet-in message. The LLDPAgent uses these packet-in messages to build a graph
// of the network topology.
//
// The topology information is stored in an LLDPMibGraph, which represents the network
// as a graph where switches and hosts are vertices and links are edges. This graph
// is used by other controller applications like LLDPBalancedMinHop to compute paths
// between hosts.
//
// The LLDPAgent installs flow entries in switches to forward LLDP packets to the
// controller. It also handles the expiration of topology information based on the
// configured timeout.
//
simple LLDPAgent like IControllerApp
{
    parameters:
        @class(openflow::LLDPAgent);
        @display("i=block/app");

        // How often to send LLDP packets for topology discovery (default value from Cisco)
        double pollInterval @unit("s") = default(30s);

        // How long topology information is valid before expiring (default value from Cisco)
        double timeOut @unit("s") = default(120s);

        // Hard timeout for flow entries (0 means no hard timeout)
        int flowModHardTimeOut = default(0);

        // Idle timeout for flow entries (how long a flow entry remains if not used)
        int flowModIdleTimeOut = default(60);

        // Whether to print the topology graph to the console
        bool printMibGraph = default(false);

        // Priority of flow entries installed by this application (higher values are matched first)
        int priority = default(1);
}
