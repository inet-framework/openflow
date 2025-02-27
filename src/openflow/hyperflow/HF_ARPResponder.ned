
package openflow.hyperflow;
import openflow.controllerApps.IControllerApp;


simple HF_ARPResponder like IControllerApp
{
    parameters:
        @class(openflow::HF_ARPResponder);
        @signal[HyperFlowReFire];
        @display("i=block/app");
         int priority = default(1);
}
