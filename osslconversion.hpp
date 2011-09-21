
#ifndef DSRP_OSSL_CONVERSION_HPP
#define DSRP_OSSL_CONVERSION_HPP

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <openssl/bn.h>
#include "common.hpp"
#include "conversionexception.hpp"

namespace DragonSRP
{
	class OsslConversion
	{
		public:
			static void bytes2bignum(const bytes &in, BIGNUM *out);
			static void bignum2bytes(BIGNUM *in, bytes& out);
	};
}

#endif
