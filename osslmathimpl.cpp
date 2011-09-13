
#include "osslmathimpl.hpp"
#include "osslhelp.hpp"

namespace Dsrp
{
	template<class HashFunctionPolicy> 
	OsslMathImpl<HashFunctionPolicy>::OsslMathImpl() :
		N(BN_new()),
		g(BN_new()),
		k(BN_new()),
		ctx(BN_CTX_new())
	{
		
	}
	
	template<class HashFunctionPolicy>
	OsslMathImpl<HashFunctionPolicy>::~OsslMathImpl()
	{
		BN_free(N);
		BN_free(g);
		BN_free(k);
		BN_CTX_free(ctx);
	}
	
	template<class HashFunctionPolicy> 
	bytes OsslMathImpl<HashFunctionPolicy>::setNg
	(Ng ng)
	{
		// checkNg()????
		// set that we set Ng as bool
		
		bytes NN = ng.getN();
		bytes gg = ng.getg();
		
		bytes2bignum(NN, N);
		bytes2bignum(gg, g);
		
		HashFunctionPolicy hf;
		bytes both = NN;
		both.insert(both.end(), gg.begin(), gg.end());
		bytes kk = hf.hash(both);
		bytes2bignum(kk, k);
	}
	
	// necessary
	// A = g^a mod N
	template<class HashFunctionPolicy>
	int OsslMathImpl<HashFunctionPolicy>::calculateA
	(const bytes &aa, bytes &A_out)
	{
		int ret = -1; // Default fail
		BIGNUM *a = BN_new();
		BIGNUM *A = BN_new();
		BIGNUM *tmp1 = BN_new();
		
		bytes2bignum(aa, a);
		BN_mod_exp(A, g, a, N, ctx);
		
		bignum2bytes(A, A_out);
		
		
		
		BN_free(a);
		BN_free(A);
		BN_free(tmp1);
		
		return ret;
	}
	
	// u = H(A || B)
	// x = H(salt || H(username || ":" || password)
	// S = (B - k*(g^x)) ^ (a + ux)
	// K = H(S)
	template<class HashFunctionPolicy>
	int OsslMathImpl<HashFunctionPolicy>::clientChallenge
	(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &K_out, bytes &M1_out)
	{
		// Safety SRP6a check necessary !!!!!!!!!!
		bool rval = -1; // default fail
		
		BIGNUM *B = BN_new();
		BIGNUM *x = BN_new();
		BIGNUM *a = BN_new();
		BIGNUM *u = BN_new();
		BIGNUM *tmp1 = BN_new();
		BIGNUM *tmp2 = BN_new();
		BIGNUM *tmp3 = BN_new();
		BIGNUM *S = BN_new();
		
		// Calculate u = H(A || B)
		HashFunctionPolicy hf;
		bytes AandB = AA;
		AandB.insert(AandB.end(), BB.begin(), BB.end());
		bytes uu = hf.hash(AandB);
		bytes2bignum(uu, u);
		bytes2bignum(BB, B);
		
		// Calculate x = HASH(salt || HASH(username || ":" || password)
		unsigned char *colon = ':';
		bytes sup = salt;
		sup.insert(sup.end(), username.begin(), username.end());
		sup.insert(sup.end(), colon, colon + 1);
		sup.insert(sup.end(), password.begin(), password.end());
		bytes hashTmp = hf.hash(sup);
		hashTmp.insert(sup.begin(), salt.begin(), salt.end());
		sup = hf.hash(hashTmp);
		bytes2bignum(sup, x);
		
		//Calculate S
		// SRP-6a safety check
		if (!BN_is_zero(B) && !BN_is_zero(u))
		{
			bytes2bignum(aa, a);
			BN_mod_mul(tmp1, u, x, N, ctx);	   /* tmp1 = ux */
			BN_mod_add(tmp2, a, tmp1, N, ctx); /* tmp2 = a+ux  */
			BN_mod_exp(tmp1, g, x, N, ctx);    /* tmp1 = (g^x)%N */
			BN_mod_mul(tmp3, k, tmp1, N, ctx); /* tmp3 = k*((g^x)%N)       */
			BN_sub(tmp1, B, tmp3);             /* tmp1 = (B-k*((g^x)%N) */
			BN_mod_exp(S, tmp1, tmp2, N, ctx); /* S = ((B-k*((g^x)%N)^(a+ux)%N) */
			
			// Calculate K
			K_out = hf.hash(S);
		
			// Calculate M1
			M1_out = calculateM1(username, salt, AA, BB, K_out);
			
			rval = 0;
		}
		
		BN_free(B);
		BN_free(x);
		BN_free(a);
		BN_free(u);
		BN_free(tmp1);
		BN_free(tmp2);
		BN_free(tmp3);
		BN_free(S);
		
		return rval;
	}
	
	
	// M = H(H(N) XOR H(g) | H(username) | s | A | B | K)
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateM1
	(const bytes &username, const bytes &s, const bytes &A, const bytes &B, const bytes &K)
	{
		HashFunctionPolicy hf;
		
		bytes NN;
		bytes gg;
		
		bignum2bytes(N, NN);
		bignum2bytes(g, gg);
		
        bytes H_N = hf.hash(NN); 
        bytes H_g = hf.hash(gg);
        
        bytes H_username = hf.hash(username);
        bytes H_xor;
		
        H_xor.resize(hf.outputLen());
		for (int i = 0; i < hf.outputLen(); i++ ) H_xor[i] = H_N[i] ^ H_g[i];
    
		bytes toHash = H_xor;
		toHash.insert(toHash.end(), H_username.begin(), H_username.end());
		toHash.insert(toHash.end(), s.begin(), s.end());
		toHash.insert(toHash.end(), A.begin(), A.end());
		toHash.insert(toHash.end(), B.begin(), B.end());
		toHash.insert(toHash.end(), K.begin(), K.end());
		
		return hf.hash(toHash);
	}
	
	template<class HashFunctionPolicy>
	int OsslMathImpl<HashFunctionPolicy>::serverChallange
	(const bytes &username, const bytes &salt, const bytes &verificator, const bytes &AA, const bytes &bb, bytes &M1_out, bytes &M2_out, bytes &K_out)
	{
		int rval = -1; // default fail
		
		HashFunctionPolicy hf;
		
		bytes SS;
		
		BIGNUM *A = BN_new();
		BIGNUM *b = BN_new();
		BIGNUM *B = BN_new();
		BIGNUM *v = BN_new();
		BIGNUM *S = BN_new();
		BIGNUM *u = BN_new();
		BIGNUM *tmp1 = BN_new();
		BIGNUM *tmp2 = BN_new();

		bytes2bignum(bb, b);
		bytes2bignum(verificator, v);
		
		// there is neccessary to add the SRP6a security check
		// SRP-6a safety check
		
        BN_mod(tmp1, A, N, ctx);
        
        // i added the v != 0 check
        if (!BN_is_zero(tmp1) && !BN_is_zero(v))
        {
		
		    // Calculate B = k*v + g^b
			BN_mod_mul(tmp1, k, v, N, ctx);
			BN_mod_exp(tmp2, g, b, N, ctx);
			BN_mod_add(B, tmp1, tmp2, N, ctx);
		
			// Calculate u = H(A || B)
			bytes AABB = AA;
			bytes BB;
			bignum2bytes(B, BB);
			
			AABB.insert(AABB.end(), BB.begin(), BB.end());
			bytes uu = hf.hash(AABB);
			bytes2bignum(uu, u);
		
			// Calculate S = (A *(v^u)) ^ b
			BN_mod_exp(tmp1, v, u, N, ctx);
			BN_mod_mul(tmp2, A, tmp1, N, ctx);
			BN_mod_exp(S, tmp2, b, N, ctx);
			bignum2bytes(S, SS);
			K_out = hf.hash(SS);
			
			// Calculate M1 = H(H(N) XOR H(g) || H (s || A || B || K))
			M1_out = calculateM1(username, salt, AA, BB, K_out);
			
			// Calculate M2 = H(A || M || K)
			bytes toHashM2 = AA;
			toHashM2.insert(toHashM2.end(), M1_out.begin(), M1_out.end());
			toHashM2.insert(toHashM2.end(), K_out.begin(), K_out.end());
			M2_out = hf.hash(toHashM2);
			
			rval = 0;
		}
		
		
		BN_free(A);
		BN_free(b);
		BN_free(B);
		BN_free(v);
		BN_free(S);
		BN_free(u);
		BN_free(tmp1);
		BN_free(tmp2);
		
		
		return rval;
	}
}
