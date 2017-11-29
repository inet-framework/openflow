
package openflow.hyperflow;
import openflow.controllerApps.AbstractControllerApp;


simple HF_ARPResponder like AbstractControllerApp
{
    parameters:
        @signal[HyperFlowReFire];
        @display("i=block/app");
}
