//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// c Timo Haeckel, for HAW Hamburg
//


package openflow.openflow.switch.flowtable;

import openflow.openflow.switch.flowtable.IOpenFlowFlowTable;

//
// [GENERATED DOCUMENTATION -- ACCURACY UNVERIFIED]
// The OF_FlowTable module implements the core packet forwarding logic of an OpenFlow switch.
// It stores flow entries that determine how packets are processed and forwarded through the switch.
//
// Each flow entry contains:
// - Match fields: Criteria for matching packets (MAC addresses, IP addresses, ports, etc.)
// - Actions: Instructions for handling matching packets (forward to port, drop, modify headers)
// - Timeouts: Idle and hard timeouts for automatic entry removal
// - Priority: Determines matching precedence when multiple entries could match
//
// Key functions:
// - Packet matching: Finding the appropriate flow entry for incoming packets
// - Flow entry management: Adding, modifying, and removing entries based on controller commands
// - Timeout handling: Automatically removing expired entries
//
// In the OpenFlow architecture:
// - The controller installs flow entries in the switch's flow table
// - When a packet arrives, it's matched against the flow table
// - If a match is found, the corresponding actions are executed
// - If no match is found, the packet is typically sent to the controller (table miss)
//
// @author Timo Haeckel, for HAW Hamburg
//
simple OF_FlowTable like IOpenFlowFlowTable
{
    parameters:
        @class(openflow::OF_FlowTable);
        @display("i=block/table2,#008002");

        // The maximum numbers of entries this table can hold,
        // if <= 0 the table size will be infinite
        int maxFlowEntries = default(0);
        // the interval to check if there are aged entries. Auto check if == 0
        double agingInterval @unit("s") = default(0s);
}
