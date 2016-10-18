

package openflow.hostApps;

import inet.applications.IPingApp;
import inet.applications.pingapp.*;

//PingAppRandom:
// choses random destination node.
//
// PingApp:
//
// Generates ping requests and calculates the packet loss and round trip
// parameters of the replies.
//
// Start/stop time, interval etc can be specified via parameters. To disable,
// specify empty destAddr or stopTime<=startTime.
//
// Every ping request is sent out with a sequence number, and replies are
// expected to arrive in the same order. Whenever there's a jump in the
// in the received ping responses' sequence number (e.g. 1, 2, 3, 5), then
// the missing pings (number 4 in this example) is counted as lost.
// Then if it still arrives later (that is, a reply with a sequence number
// smaller than the largest one received so far) it will be counted as
// out-of-sequence arrival. So the number of really lost pings will be
// "lost" minus "out-of-order" (assuming there's no duplicate or bogus reply).
//
// Uses PingPayload as payload for the ICMP(v6) Echo Request/Reply packets.
//
// @see PingPayload, ICMP, ICMPv6Core
//
simple PingAppRandom extends inet.applications.pingapp.PingApp{
    parameters:
        @signal[pingPacketHash](type="long");
        @statistic[pingPacketHash](title="PingPacketHash"; record=vector?,stats?; interpolationmode=none);
        string destinationNedType = default("inet.nodes.inet.StandardHost");
        @display("i=block/app");
        @class(PingAppRandom);
}


