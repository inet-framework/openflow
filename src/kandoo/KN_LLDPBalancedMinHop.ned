

package openflow.kandoo;
import openflow.controllerApps.*;

simple KN_LLDPBalancedMinHop like AbstractControllerApp
{
    parameters:
        @display("i=block/app");
        int flowModHardTimeOut = default(0);
        int flowModIdleTimeOut = default(1);
        bool printMibGraph = default(false);
        bool dropIfNoRouteFound = default(true);
        bool ignoreArpRequests = default(false);
        
}
