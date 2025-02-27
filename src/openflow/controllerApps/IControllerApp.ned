//
// Copyright (C) 2004 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


package openflow.controllerApps;

//
// Module interface for all OpenFlow controller applications. Controller
// applications are modules that implement specific control logic for an
// OpenFlow network. They run within an OpenFlow controller and make decisions
// about how packets should be handled by OpenFlow switches. Examples include
// learning switches, routing applications, load balancers, and security
// applications.
//
// The controller application architecture follows a modular design where
// multiple applications can be installed in a single controller, each handling
// different aspects of network control. Applications receive events from the
// controller (like packet-in messages from switches), process them according to
// their logic, and respond with appropriate actions (like sending flow
// modification messages to install flow entries in switches).
//
// Signal Definitions:
// - PacketIn: Emitted when a packet-in message is received from a switch
// - PacketOut: Emitted when a packet-out message is sent to a switch
// - PacketFeatureRequest: Emitted when a feature request message is sent to a switch
// - PacketFeatureReply: Emitted when a feature reply message is received from a switch
// - PacketExperimenter: Emitted for experimenter (vendor) messages
// - Booted: Emitted when the controller has completed initialization
//
moduleinterface IControllerApp
{
    parameters:
        @class(openflow::IControllerApp);
        @signal[PacketIn];
        @signal[PacketOut];
        @signal[PacketFeatureRequest];
        @signal[PacketFeatureReply];
        @signal[PacketExperimenter];
        @signal[Booted];
        @display("i=block/app");

        // Priority of flow entries installed by this application (higher values are matched first)
        // In OpenFlow, when multiple flow entries match a packet, the entry with the highest
        // priority is used. This parameter determines the priority value set in flow modification
        // messages sent by this controller application.
        int priority;
}


