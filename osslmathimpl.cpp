
#include "osslmathimpl.hpp"
#include "osslhelp.hpp"

namespace Dsrp
{
	template<class HashFunctionPolicy> 
	OsslMathImpl<HashFunctionPolicy>::OsslMathImpl() :
		N(BN_new()),
		g(BN_new())
	{
		
	}
	
	template<class HashFunctionPolicy>
	OsslMathImpl<HashFunctionPolicy>::~OsslMathImpl()
	{
		BN_free(N);
		BN_free(g);
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
