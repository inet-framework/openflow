

package openflow.utility;

// Calculates a Spanning Tree in the OpenFlow network.
// The purpose is to prevent packet loops in the network.
simple StaticSpanningTree
{
    parameters:
		@class(openflow::StaticSpanningTree);
        @display("i=openflow/spanning-tree");
        string NodeType = default("openflow.openflow.switch.Open_Flow_Switch");
        int startNode = default(0);
}
