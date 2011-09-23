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


#ifndef DSRP_USERNOTFOUNDEXCEPTION_HPP
#define DSRP_USERNOTFOUNDEXCEPTION_HPP

#include "common.hpp"
#include "dsrpexception.hpp"

namespace DragonSRP
{
	class UserNotFoundException : public DsrpException
	{
		public:
			UserNotFoundException(const char *message, const bytes &userName);
			UserNotFoundException(std::string &message, const bytes &userName);
			bytes getUsername();
		
		private:
			bytes username;
	};
	
}

#endif
