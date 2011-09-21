
#ifndef DSRP_CONVERSION_HPP
#define DSRP_CONVERSION_HPP

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <openssl/bn.h>
#include "common.hpp"
#include "conversionexception.hpp"

namespace DragonSRP
{
	class Conversion
	{
		public:
			// BIGNUM
			static void bytes2bignum(const bytes &in, BIGNUM *out);
			static void bignum2bytes(BIGNUM *in, bytes& out);
			
			static unsigned char *bytes2array(const bytes &in, int *lenout); // must free()
			static bytes array2bytes(const unsigned char *in, int len);
			
			// string2bytes
			static bytes string2bytes(const std::string &str);
			static bytes string2bytes(const char *str);
		
	};
}

#endif
