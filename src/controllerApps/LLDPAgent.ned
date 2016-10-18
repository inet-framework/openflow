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

simple LLDPAgent like AbstractControllerApp
{
    parameters:
        @display("i=block/app");
        
        //default value cisco
        double pollInterval @unit("s") = default(30s);
        
        //default value cisco
        double timeOut @unit("s") = default(120s);
        int flowModHardTimeOut = default(0);
        int flowModIdleTimeOut = default(60);
        bool printMibGraph = default(false);
        
}
