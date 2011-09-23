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


#include "srpclientauthenticator.hpp"
#include "dsrpexception.hpp"

namespace DragonSRP
{
	SrpClientAuthenticator::SrpClientAuthenticator(const bytes &userName, 
				const bytes &passWord, const bytes &aa, const bytes &AA) :
			username(userName),
			password(passWord),
			a(aa),
			A(AA)
		
	{
		
	}
	
	bytes SrpClientAuthenticator::getSessionKey(bytes M2_from_server)
	{
		if (M2_from_server != M2_calculated) throw DsrpException("Authentification failed, bad password");
		return K;
	}
	
	bytes SrpClientAuthenticator::getA()
	{
		return A;
	}
}
