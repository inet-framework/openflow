package openflow.kandoo;

import openflow.controllerApps.AbstractControllerApp;

simple KN_ARPResponder like AbstractControllerApp
{
    parameters:
        @signal[KandooEvent];
        @display("i=block/app");
}
