package openflow.utility;

// Calculates a Spanning Tree in the OpenFlow network.
// The purpose is to prevent packet loops in the network.
simple ControllerInvolvementFilter
{
    parameters:
        @class(openflow::ControllerInvolvementFilter);
        @signal[pingPacketHash](type="long");
        @statistic[pingPacketHash](title="PingPacketHash"; record=vector?,stats?; interpolationmode=none);
        @display("i=spanning-tree");
}
