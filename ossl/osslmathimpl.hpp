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
*  This product includes software developed by the OpenSSL Project  *
*  for use in the OpenSSL Toolkit. (http://www.openssl.org/)        *
*                                                                   *
*  This product includes cryptographic software                     *
*  written by Eric Young (eay@cryptsoft.com)                        *
*                                                                   *
*  This product includes software                                   *
*  written by Tim Hudson (tjh@cryptsoft.com)                        *
@  =============================================================== */


#ifndef DSRP_OSSLMATHIMPL_HPP
#define DSRP_OSSLMATHIMPL_HPP

#include <openssl/bn.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>

#include "dsrp/common.hpp"
#include "dsrp/mathinterface.hpp"
#include "dsrp/ng.hpp"
#include "dsrp/conversion.hpp"

#include "dsrp/dsrpexception.hpp"

namespace DragonSRP
{
namespace Ossl
{
	
	class OsslMathImpl : public MathInterface
	{
		public:
			OsslMathImpl(HashInterface &hashInterface, Ng ngVal);
			~OsslMathImpl();
			bytes calculateA(const bytes &aa);
			void clientChallange(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &M1_out, bytes &M2_out, bytes &K_out);
			void serverChallange(const bytes &username, const bytes &salt, const bytes &verificator, const bytes &AA, const bytes &bb, bytes &B_out, bytes &M1_out, bytes &M2_out, bytes &K_out);
		private:
			bytes calculateM1(const bytes &username, const bytes &s, const bytes &A, const bytes &B, const bytes &K);
			void checkNg();
			
			BIGNUM *N;
			BIGNUM *g;
			BIGNUM *k;
			BN_CTX *ctx;
	};
	
// Namespace endings
}
}

#endif
