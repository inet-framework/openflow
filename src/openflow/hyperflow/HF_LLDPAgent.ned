

package openflow.hyperflow;
import openflow.controllerApps.AbstractControllerApp;


simple HF_LLDPAgent like AbstractControllerApp
{
    parameters:
        @class(openflow::HF_LLDPAgent);
        @signal[HyperFlowReFire];
        @display("i=block/app");

        //default value cisco
        double pollInterval @unit("s") = default(30s);

        //default value cisco
        double timeOut @unit("s") = default(120s);
        int flowModHardTimeOut = default(0);
        int flowModIdleTimeOut = default(60);
        bool printMibGraph = default(false);
        int priority = default(1);

}
