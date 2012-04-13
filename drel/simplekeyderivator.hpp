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

/* ===============================================================  @
*  In addition, as a special exception, the copyright holders give  *
*  permission to link the code of portions of this program with the *
*  OpenSSL library under certain conditions as described in each    *
*  individual source file, and distribute linked combinations       *
*  including the two.                                               *
*  You must obey the GNU Lesser General Public License in all       *
*  respects for all of the code used other than OpenSSL.            *
*  If you modify file(s) with this exception, you may extend        *
*  this exception to your version of the file(s), but you are not   *
*  obligated to do so.  If you do not wish to do so, delete this    *
*  exception statement from your version. If you delete this        *
*  exception statement from all source files in the program, then   *
*  also delete it here.                                             *
@  =============================================================== */

#ifndef DSRP_SIMPLEKEYDERIVATOR_HPP
#define DSRP_SIMLPEKEYDERIVATOR_HPP

#include <vector>
#include "../dsrp/common.hpp"
#include "../dsrp/dsrpexception.hpp"
#include "../dsrp/hashinterface.hpp"

namespace DragonSRP
{
	class SimpleKeyDerivator
	{
		public:
			// MacKey length must have at lest hash.blockLen() bytes !!!!!!
			SimpleKeyDerivator(const bytes &sessionSrpKey, unsigned int blockCipherKeyBytes, unsigned int blockCipherIVBytes, unsigned int macKeyBytes);
			
			bytes &getClientEncryptionKey(){return mClientEncryptionKey;}
			bytes &getClientIV(){return mClientIV;}
			bytes &getClientMacKey(){return mClientMacKey;}
			
			bytes &getServerEncryptionKey(){return mServerEncryptionKey;}
			bytes &getServerIV(){return mServerIV;}
			bytes &getServerMacKey(){return mServerMacKey;}
			
		private:
			bytes mClientEncryptionKey;
			bytes mClientIV;
			bytes mClientMacKey;
			
			bytes mServerEncryptionKey;
			bytes mServerIV;
			bytes mServerMacKey;
			
			
	};
	
}

#endif
