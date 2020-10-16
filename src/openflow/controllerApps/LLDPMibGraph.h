

#ifndef LLDPMIBGRAPH_H_
#define LLDPMIBGRAPH_H_

#include "openflow/controllerApps/LLDPMib.h"
#include <string>
#include <algorithm>

using namespace __gnu_cxx;

namespace openflow{

class LLDPMibGraph {
    public:
        LLDPMibGraph();

        bool addEntry(std::string src, int srcPort, std::string dst, int dstPort, SimTime timeOut);
        void removeExpiredEntries();


        long getNumOfEdges() const;
        long getNumOfVerticies() const;

        const std::string getStringGraph();
        const std::map<std::string, std::vector<LLDPMib> >& getVerticies() const;
        long getVersion() const;

    protected:
        std::map< std::string, std::vector<LLDPMib> > verticies;
        long numOfVerticies;
        long numOfEdges;
        long version;
};

} /*end namespace openflow*/

#endif /* FLOW_TABLE_H_ */
