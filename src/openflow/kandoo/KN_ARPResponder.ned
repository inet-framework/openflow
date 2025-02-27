package openflow.kandoo;

import openflow.controllerApps.IControllerApp;

simple KN_ARPResponder like IControllerApp
{
    parameters:
        @class(openflow::KN_ARPResponder);
        @signal[KandooEvent];
        @display("i=block/app");
     	int priority = default(1);
}
