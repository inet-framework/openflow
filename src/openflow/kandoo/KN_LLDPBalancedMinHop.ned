package openflow.kandoo;

import openflow.controllerApps.AbstractControllerApp;

simple KN_LLDPBalancedMinHop like AbstractControllerApp
{
    parameters:
        @signal[KandooEvent];
        @display("i=block/app");
        int flowModHardTimeOut = default(0);
        int flowModIdleTimeOut = default(1);
        bool printMibGraph = default(false);
        bool dropIfNoRouteFound = default(true);
        bool ignoreArpRequests = default(false);
}
