
#ifndef OPENFLOWGRAPHANALYZER_H_
#define OPENFLOWGRAPHANALYZER_H_

#include <omnetpp.h>
#include "openflow/openflow/switch/OF_Switch.h"

class Node;

namespace openflow{

class OpenFlowGraphAnalyzer : public cSimpleModule
{

public:
    virtual void finish();


protected:
        cTopology topo;

        std::list<std::list<cTopology::Node *> > computedPaths;
        std::list<cTopology::Node * > getShortestPath(cTopology::Node * src, cTopology::Node * trg);

        int maxPathLength;
        int minPathLength;
        double avgPathLength;
        int numClientNodes;
        int numSwitchNodes;
        double avgNumSwitchLinks;
        bool considerOnlyEndToEnd;

        std::map<std::string,int> swMap;
        std::map<std::string,int> clMap;


        virtual int numInitStages() const  {return NUM_INIT_STAGES;}
        virtual void initialize(int stage);
        virtual void handleMessage(cMessage *msg);
};

} /*end namespace openflow*/

#endif /* SPANNINGTREE_H_ */
