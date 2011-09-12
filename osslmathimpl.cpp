
#include "osslmathimpl.hpp"
#include "osslhelp.hpp"

namespace Dsrp
{
	template<class HashFunctionPolicy> 
	OsslMathImpl<HashFunctionPolicy>::OsslMathImpl() :
		N(BN_new()),
		g(BN_new()),
		ctx(BN_CTX_new())
	{
		
	}
	
	template<class HashFunctionPolicy>
	OsslMathImpl<HashFunctionPolicy>::~OsslMathImpl()
	{
		BN_free(N);
		BN_free(g);
		BN_CTX_free(ctx);
	}
	
	template<class HashFunctionPolicy> 
	bytes OsslMathImpl<HashFunctionPolicy>::setNg
	(Ng<HashFunctionPolicy> ng)
	{
		// checkNg()????
		// set that we set Ng as bool
		bytes2bignum(ng.getN(), N);
		bytes2bignum(ng.getg(), g);
	}
	
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateA
	(bytes aa)
	{
		BIGNUM *a = BN_new();
		BIGNUM *A = BN_new();
		
		bytes2bignum(aa, a);
		BN_mod_exp(A, g, a, N, ctx); // A = g^a mod N
		
		bytes ret;
		bignum2bytes(A, ret);
		
		BN_free(a);
		BN_free(A);
		
		return ret;
	}
	
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateB
	(bytes verificator, bytes b)
	{
		
	}
	
	// S = (A *(v^u)) ^ b
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateSserver
	(bytes A, bytes verificator, bytes u, bytes b)
	{
		
	}
	
	template<class HashFunctionPolicy> 
	bytes OsslMathImpl<HashFunctionPolicy>::calculateSclient
	(bytes B, bytes x, bytes a, bytes u)
	{
		
	}
	
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::generateRandom
	(unsigned int bits)
	{
		
	}
}
