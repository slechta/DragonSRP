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


#include <iostream>
#include "osslconversion.hpp"

namespace DragonSRP
{
	void OsslConversion::bytes2bignum(const bytes &in, BIGNUM *out)
	{
		unsigned char *bytesIn = (unsigned char*) malloc(sizeof(unsigned char) * in.size());
		// should check if bytesIn==NULL !!!!!
		copy(in.begin(), in.end(), bytesIn);
		BN_bin2bn(bytesIn, in.size(), out);
		free(bytesIn);
	}
	
	void OsslConversion::bignum2bytes(BIGNUM *in, bytes& out)
	{
		unsigned char *arr = (unsigned char *) malloc(sizeof(unsigned char) * BN_num_bytes(in));
		// should check if bytesIn==NULL !!!!!
		int len = BN_bn2bin(in, arr);
		out.resize(len); // important, otherwise SIGSEGV
		copy(arr, arr + len, out.begin());
		free(arr);
	}
	
	void OsslConversion::printBignum(const BIGNUM *in)
	{
		char *str = BN_bn2hex(in);
		std::cout << str << std::endl;
		//OPENSSL_free(str);
		free(str); // ugly!
	}
}
