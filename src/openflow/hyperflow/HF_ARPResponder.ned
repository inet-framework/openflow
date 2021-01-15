
package openflow.hyperflow;
import openflow.controllerApps.AbstractControllerApp;


simple HF_ARPResponder like AbstractControllerApp
{
    parameters:
        @class(openflow::HF_ARPResponder);
        @signal[HyperFlowReFire];
        @display("i=block/app");
         int priority = default(1);
}
