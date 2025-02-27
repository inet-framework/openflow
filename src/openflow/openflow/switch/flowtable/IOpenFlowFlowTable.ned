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
// (c) Timo Haeckel, for HAW Hamburg
//


package openflow.openflow.switch.flowtable;

//
// Interface for OpenFlow flow tables, which are a core component of the OpenFlow
// switch architecture. Flow tables store the forwarding rules (flow entries) that
// determine how packets are processed by the switch.
//
// The default implementation is ~OF_FlowTable.
//
// @author Timo Haeckel, for HAW Hamburg
//
moduleinterface IOpenFlowFlowTable
{
    parameters:
        @display("i=block/table2,#008002");

        // The maximum numbers of entries this table can hold,
        // if <= 0 the table size will be infinite
        int maxFlowEntries;

        // The interval to check if there are no entries. Auto check if == 0.
        double agingInterval @unit("s");
}

