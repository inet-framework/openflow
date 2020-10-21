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

//
// Interface module for OpenFlow FlowTables implementing the flow table management.
//

//
// Prototype for modules providing OpenFlow table functionality to OpenFlow rule based switches (@see ~IOpenFlowRelayUnit).
// These modules provide OpenFlow table memory management with finite size.
//
// Functions:
// - manages OpenFlow TableEntries  (@see ~OF_FlowTableEntry)
// - models finite table size
//
//
// This module is not a concrete implementation, it just defines gates and
// parameters a ~IOpenFlowFlowTable should have. Concrete inplementations add
// capacity and performance aspects to the model.
//
// Known implementations are ~OF_FlowTable
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
        // the interval to check if there are no entries. Auto check if == 0
        double agingInterval @unit("s");
}

