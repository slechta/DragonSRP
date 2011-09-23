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


#ifndef DSRP_SRPCLIENT_HPP
#define DSRP_SRPCLIENT_HPP

#include "common.hpp"

#include "mathinterface.hpp"
#include "randominterface.hpp"

#include "srpclientauthenticator.hpp"

namespace DragonSRP
{	
	class SrpClient
	{		
		public:
			SrpClient(MathInterface &mathInterface, RandomInterface &randomInterface);
			SrpClientAuthenticator getAuthenticator(bytes username, bytes password);
			bytes getM1(bytes salt, bytes B, SrpClientAuthenticator &sca);

		private:
			MathInterface &math;
			RandomInterface &random;	
	};
}

#endif
