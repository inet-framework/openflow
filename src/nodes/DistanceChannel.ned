
package openflow.nodes;
import inet.common.misc.ThruputMeteringChannel;


// uses the geographical distance between two nodes and calculates the delay.
channel DistanceChannel extends ThruputMeteringChannel
{
    double distance @unit(m) = default(0m);
    delay = this.distance / 200000km * 1s;
    datarate = 10Gbps;
    thruputDisplayFormat = "u";
}
