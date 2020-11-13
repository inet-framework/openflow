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

#ifndef OPENFLOW_OPENFLOW_PROTOCOL_OF100MATCHBUILDER_H_
#define OPENFLOW_OPENFLOW_PROTOCOL_OF100MATCHBUILDER_H_

#include <openflow/openflow/protocol/OFMatchFactory.h>

namespace openflow {

class OF100MatchBuilder : public OFMatchBuilder{
public:
    OF100MatchBuilder() : OFMatchBuilder(){}
    virtual ~OF100MatchBuilder(){}

    virtual OFMatchBuilder* setField(oxm_ofb_match_fields field, void* value);

};

} /* namespace openflow */

#endif /* OPENFLOW_OPENFLOW_PROTOCOL_OF100MATCHBUILDER_H_ */
