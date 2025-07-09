

package openflow.kandoo;
import openflow.controllerApps.LLDPForwarding;


simple KN_LLDPForwarding extends LLDPForwarding
{
    parameters:
        @class(openflow::KN_LLDPForwarding);
        @signal[KandooEvent];
        @signal[cpPingPacketHash](type="unsigned long");
        @statistic[cpPingPacketHash](title="CpPingPacketHash"; record=vector?,stats; interpolationmode=none);
}
