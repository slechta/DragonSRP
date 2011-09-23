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


#include <stdio.h>
#include <iterator>
#include "memorylookup.hpp"
#include "user.hpp"
#include "usernotfoundexception.hpp"

namespace DragonSRP
{
	class User;
	
	User MemoryLookup::getByName(bytes username)
	{
		std::map<bytes, User>::iterator iter;
		iter = db.find(username);
		if (iter == db.end()) throw UserNotFoundException("User not found.", username);
		return iter->second;
	}
	
	bool MemoryLookup::userAdd(User user)
	{
		std::pair<std::map<bytes, User>::iterator, bool> ret = db.insert(make_pair(user.getUsername(), user));
		return ret.second;
	}
}
