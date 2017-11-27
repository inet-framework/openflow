

#ifndef STATICSPANNINGTREE_H_
#define STATICSPANNINGTREE_H_

#include <omnetpp.h>
#include "OF_Switch.h"

class StaticSpanningTree : public cSimpleModule
{
protected:
    struct NodeInfo {
            NodeInfo() {isInTree=false;isProcessed=false;}
            bool isInTree;
            bool isProcessed;
            int moduleID;
            std::vector<int> ports;
            std::vector<int> treeNeighbors;
        };

        typedef std::vector<NodeInfo> NodeInfoVector;
        cTopology topo_spanntree;
        NodeInfoVector nodeInfo;

        virtual int numInitStages() const  {return 5;}
        virtual void initialize(int stage);
        virtual void handleMessage(cMessage *msg);
};


#endif /* SPANNINGTREE_H_ */
