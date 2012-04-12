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
			void clientChallange(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &M1_out, bytes &M2_out, bytes &K_out, bool interleave = false);
			void serverChallange(const bytes &username, const bytes &salt, const bytes &verificator, const bytes &AA, const bytes &bb, bytes &B_out, bytes &M1_out, bytes &M2_out, bytes &K_out, bool interleave = false);
			bytes calculateVerificator(const bytes &username, const bytes &password, const bytes &salt);
			
			#ifdef DSRP_DANGEROUS_TESTING
				bytes S_client_premaster_secret;
				bytes S_server_premaster_secret;
				bytes u_server;
				bytes k_math;
				bytes x_client;
				bytes x_vgen;
			#endif
			
		private:
			bytes calculateM1(const bytes &username, const bytes &s, const bytes &A, const bytes &B, const bytes &K);
			void checkNg();
			
			void interleaveS(const bytes &S, bytes &K); // input S, returns K
			
			BIGNUM *N;
			BIGNUM *g;
			BIGNUM *k;
			BN_CTX *ctx;
	};
	
// Namespace endings
}
}

#endif
