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


#ifndef DSRP_SRPVERIFICATOR_HPP
#define DSRP_SRPVERIFICATOR_HPP

#include "common.hpp"
#include "user.hpp"
#include "dsrpexception.hpp"

namespace DragonSRP
{
	class SrpVerificator
	{
		public:
			SrpVerificator(bytes userName, bytes userSalt, bytes B, bytes calculated_M1, bytes calculated_M2, bytes K);
			bytes getSalt();
			bytes getB();
			bytes getUsername();
			void authenticate(const bytes &M1_from_client, bytes &M2_to_client, bytes &session_K);
					
		private:
			bytes salt;
			bytes BB;
			bytes calc_M1;
			bytes calc_M2;
			bytes KK; // session key
			bytes username;
	};
	
}

#endif
