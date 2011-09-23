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


#ifndef DSRP_SRPCLIENTAUTHENTICATOR_HPP
#define DSRP_SRPCLIENTAUTHENTICATOR_HPP

#include "common.hpp"

namespace DragonSRP
{
	class SrpClientAuthenticator
	{
		friend class SrpClient; // To set K and M2_calculated
		
		public:
			SrpClientAuthenticator(const bytes &userName, const bytes &passWord, const bytes &aa, const bytes &AA);
			bytes getA();
			bytes getSessionKey(bytes M2_from_server);
		
		private:
			bytes username;
			bytes password;
			bytes a;
			bytes A;
			bytes K;
			bytes M2_calculated;
			
	};
}

#endif
