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


#include "srpverificator.hpp"

namespace DragonSRP
{
	SrpVerificator::SrpVerificator(bytes userName, bytes userSalt, bytes B, bytes calculated_M1, bytes calculated_M2, bytes K)
		: salt(userSalt),
		BB(B),
		calc_M1(calculated_M1), 
		calc_M2(calculated_M2),
		username(userName),
		KK(K)
	{
				
	}
	
	bytes SrpVerificator::getSalt()
	{
		return salt;
	}
	
	bytes SrpVerificator::getB()
	{
		return BB;
	}
	
	bytes SrpVerificator::getUsername()
	{
		return username;
	}
	

	void SrpVerificator::authenticate(const bytes &M1_from_client, bytes &M2_to_client, bytes &session_K)
	{
		if (calc_M1 != M1_from_client) throw DsrpException("Authentification failed; possibly wrong password");
		M2_to_client = calc_M2;
		session_K = KK;
	}

}
