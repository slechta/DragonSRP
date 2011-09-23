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


#include "srpserver.hpp"

namespace DragonSRP
{
	
	SrpServer::SrpServer(LookupInterface &lookupInterface, MathInterface &mathInterface, RandomInterface &randomInterface) :
		lookup(lookupInterface),
		math(mathInterface),
		random(randomInterface)
	{
			
	}	
	
	SrpVerificator SrpServer::getVerificator(const bytes &username, const bytes &AA)
	{
		// check status of authentification
		User usr = lookup.getByName(username); // throws if not found
		bytes M1, M2, K, B;
		bytes b = random.getRandom(32); // WTF? dont know how much, throws on error
		math.serverChallange(username, usr.getSalt(), usr.getVerificator(), AA, b, B, M1, M2, K); // throws on error
		return SrpVerificator(username, usr.getSalt(), B, M1, M2, K);
	}
			
	
	
}
