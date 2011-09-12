
#ifndef DSRP_OSSLMATHIMPL_HPP
#define DSRP_OSSLMATHIMPL_HPP

#include <openssl/bn.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>


#include "mathfunctions.hpp"

namespace Dsrp
{
	template<class HashFunctionPolicy>
	class OsslMathImpl // zdedit asi fakt ne
	{
		protected:
			OsslMathImpl();
			~OsslMathImpl();
			bytes setNg(Ng<HashFunctionPolicy> ng); // Must be called first
			bytes calculateB(bytes verificator, bytes b);
			bytes calculateSserver(bytes A, bytes verificator, bytes u, bytes b);
			bytes calculateSclient(bytes B, bytes x, bytes a, bytes u);
			bytes generateRandom(unsigned int bits);
			
		private:
			BIGNUM *N;
			BIGNUM *g;
	};
}

#endif
