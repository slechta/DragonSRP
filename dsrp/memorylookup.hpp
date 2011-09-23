/* ===============================================================  @
*  DragonSRP, C++ library implementing Secure Remote Protocol       *
*  Copyright (C) 2011 Pavel Slechta                                 *
*  <slechta@email.cz>                                               *
*                                                                   *
*  DragonSRP is free software; you can redistribute it and/or       *
*  modify it under the terms of the GNU Lesser General Public       *
*  License as published by the Free Software Foundation; either     *
*  version 3 of the License, or (at your option) any later version. *
*                                                                   *
*  DragonSRP is distributed in the hope that it will be useful,     *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU *
*  Lesser General Public License for more details.                  *
*                                                                   *
*  You should have received a copy of the GNU Lesser General Public *
*  License along with DragonSRP.                                    *
*  If not, see <http://www.gnu.org/licenses/>.                      *
@  =============================================================== */


#ifndef DSRP_MEMORYLOOKUP_HPP
#define DSRP_MEMORYLOOKUP_HPP

#include <map>
#include "common.hpp"
#include "lookupinterface.hpp"
#include "user.hpp"

namespace DragonSRP
{
	class MemoryLookup : public LookupInterface
	{
		public:
			User getByName(bytes username); // throws DsrpException if user not found
			bool userAdd(User user); // returns true on success
			
		private:
			std::map<bytes, User> db;
	};
}

#endif
