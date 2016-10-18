

import inet.applications.ITCPApp;
import openflow.controllerApps.*;

package openflow.kandoo;



simple KandooAgent extends openflow.controllerApps.AbstractTCPControllerApp
{
    parameters:
        @display("i=block/app");
        @class(KandooAgent);
        int flowModHardTimeOut = default(0);
        int flowModIdleTimeOut = default(1);
        int localPort = default(-1);
        string localAddress = default("");
        
        string connectAddressRootController = default("root_controller");
        int connectPortRootController = default(1003);
        
        double connectAt @unit("s") = default(1s);
        
        bool isRootController = default(false);        
       
 
        
}
