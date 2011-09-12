
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
			bytes calculateA(bytes aa); // a must be random
			bool AisOK(bytes AA);
			bytes calculateB(bytes verificator, bytes bb); // b must be random
			bytes calculateU(bytes AA, bytes BB);
			bytes calculateSserver(bytes AA, bytes verificator, bytes uu, bytes bb);
			bool calculateSclient(const bytes &BB, const bytes &xx, const bytes &aa, const bytes &uu, bytes &Sout);
			bytes generateRandom(unsigned int bits);
			
			
			int clientChallenge(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &S_out, bytes &M1_out);
			bytes calculateM1(const bytes &username, const bytes &s, const bytes &A, const bytes &B, const bytes &K);
			
			
		private:
			BIGNUM *N;
			BIGNUM *g;
			BIGNUM *k;
			BN_CTX *ctx;
	};
}

#endif
