

package openflow.openflow.switch;

////The Switch Application module is a TCP application and therefore directly connected
//to the TCP module. It belongs to the control plane and is responsible for
//the communication with the controller.
simple OF_Switch
{
    parameters:
        @signal[cpPingPacketHash](type="long");
        @statistic[cpPingPacketHash](title="CpPingPacketHash"; record=vector?,stats; interpolationmode=none);
        @signal[dpPingPacketHash](type="long");
        @statistic[dpPingPacketHash](title="DpPingPacketHash"; record=vector?,stats; interpolationmode=none);
        @signal[queueSize](type="long");
        @statistic[queueSize](title="QueueSize"; record=vector?,stats; interpolationmode=none);
        @signal[bufferSize](type="long");
        @statistic[bufferSize](title="BufferSize"; record=vector?,stats; interpolationmode=none);
        @signal[waitingTime](type="simtime_t");
        @statistic[waitingTime](title="WaitingTime"; record=vector?,stats?; interpolationmode=none);
        @display("i=block/app");
        
        string localAddress = default("");
        int localPort = default(-1);
        string connectAddress = default("");
        int connectPort = default(6633);
        
		double flowTimeoutPollInterval @unit("s") = default(1s);
		double connectAt @unit("s") = default(1s);
		double serviceTime @unit("s") = default(0s);
		int bufferCapacity = default(0);

		bool sendCompletePacket = default(false);
		bool highlightActivePorts = default(false);

        gates:
        input controlPlaneIn @labels(TCPCommand/up);
        output controlPlaneOut @labels(TCPCommand/down);
        
        input  dataPlaneIn[];
        output dataPlaneOut[];

}
