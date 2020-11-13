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

#include "openflow/openflow/protocol/OFMatchFactory.h"
#include "openflow/openflow/protocol/OF100MatchBuilder.h"
#include <string>

using namespace std;

namespace openflow {

std::unique_ptr<OFMatchBuilder> OFMatchFactory::getBuilder(){
#if OFP_VERSION_IN_USE == OFP_100
        return std::unique_ptr<OFMatchBuilder>(new OF100MatchBuilder());
#endif
}

} /* namespace openflow */
