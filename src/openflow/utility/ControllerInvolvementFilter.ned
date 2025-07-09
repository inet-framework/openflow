package openflow.utility;

// Calculates a Spanning Tree in the OpenFlow network.
// The purpose is to prevent packet loops in the network.
simple ControllerInvolvementFilter
{
    parameters:
        @class(openflow::ControllerInvolvementFilter);
        @display("i=openflow/spanning-tree");
}
