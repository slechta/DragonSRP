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


#ifndef DSRP_SRPSERVER_HPP
#define DSRP_SRPSERVER_HPP

#include "common.hpp"

#include "user.hpp"

#include "lookupinterface.hpp"
#include "hashinterface.hpp"
#include "mathinterface.hpp"
#include "randominterface.hpp"
#include "srpverificator.hpp"

#include "ng.hpp"

namespace DragonSRP
{
	class SrpServer
	{	
		public:
			SrpServer(LookupInterface &lookupInterface, MathInterface &mathInterface, RandomInterface &randomInterface);
			SrpVerificator getVerificator(const bytes &username, const bytes &AA);
			
			
		private:
			LookupInterface &lookup;
			MathInterface &math;
			RandomInterface &random;
	};
}


#endif
