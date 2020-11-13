//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// c Timo Haeckel, for HAW Hamburg
//


#ifndef OPENFLOW_OPENFLOW_UTIL_OFMATCHFACTORY_H_
#define OPENFLOW_OPENFLOW_UTIL_OFMATCHFACTORY_H_

#include "openflow/openflow/protocol/OpenFlow.h"
#include <memory>

namespace openflow {
    class OFMatchBuilder;
}

namespace openflow {

/**
 * Class for static OFMatchFactory creation.
 * Provides access to a match factory for the openflow version currently in use.
 *
 * @author Timo Haeckel, for HAW Hamburg
 */
class OFMatchFactory {
public:
    /**
     * Creates a match builder for the current openflow version. Make sure to delete it!
     */
    static std::unique_ptr<OFMatchBuilder> getBuilder();
};

class OFMatchBuilder {
public:
    OFMatchBuilder(){
        match.wildcards = OFPFW_ALL;
    }
    virtual ~OFMatchBuilder(){}

    /**
     * Set one field defined in the openflow protocol with the value.
     * @param oxm_ofb_match_fields the field to set
     * @param value the value to set for the field
     *
     * @return this match builder
     */
    virtual OFMatchBuilder* setField(oxm_ofb_match_fields field, void* value) = 0;

    oxm_basic_match build(){
        return match;
    }
protected:
    oxm_basic_match match;
};

} /* namespace openflow */

#endif /* OPENFLOW_OPENFLOW_UTIL_OFMATCHFACTORY_H_ */
