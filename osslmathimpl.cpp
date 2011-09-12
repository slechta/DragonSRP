
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
	(Ng<HashFunctionPolicy> ng)
	{
		// checkNg()????
		// set that we set Ng as bool
		bytes2bignum(ng.getN(), N);
		bytes2bignum(ng.getg(), g);
		bytes2bignum(ng.getk(), k);
	}
	
	// A = g^a mod N
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateA
	(bytes aa)
	{
		BIGNUM *a = BN_new();
		BIGNUM *A = BN_new();
		
		bytes2bignum(aa, a);
		BN_mod_exp(A, g, a, N, ctx);
		
		bytes ret;
		bignum2bytes(A, ret);
		
		BN_free(a);
		BN_free(A);
		
		return ret;
	}
	
	// constraint safety check implementation !(A%N==0)
	template<class HashFunctionPolicy>
	bool OsslMathImpl<HashFunctionPolicy>::AisOK(bytes AA)
	{
		/* SRP-6a safety check */
		BIGNUM *A = BN_new();
		BIGNUM *tmp1 = BN_new();
		
		bytes2bignum(AA, A);
		
		BN_mod(tmp1, A, N, ctx);
		bool ret = !BN_is_zero(tmp1);
		BN_free(A);
		BN_free(tmp1);
		return ret;
	}
	
	// B = k*v + g^b
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateB
	(bytes verificator, bytes bb)
	{
		BIGNUM *b = BN_new();
		BIGNUM *B = BN_new();
		BIGNUM *v = BN_new();
		BIGNUM *tmp1 = BN_new();
		BIGNUM *tmp2 = BN_new();

		bytes2bignum(bb, b);
		bytes2bignum(verificator, v);
		
		// there is neccessary to add the SRP6a security check
		// /* SRP-6a safety check */
        //  BN_mod(tmp1, A, ng->N, ctx);
		
		BN_mod_mul(tmp1, k, v, N, ctx); // tmp1 = k * v
        BN_mod_exp(tmp2, g, b, N, ctx); // tmp2 = (g ^ b) % N
        BN_mod_add(B, tmp1, tmp2, N, ctx); // B = k * v + (g ^ b) % N
		
		bytes ret;
		bignum2bytes(B, ret);
		
		BN_free(b);
		BN_free(v);
		BN_free(tmp1);
		BN_free(tmp2);
		BN_free(B);
		
		return ret;
	}
	
	
	// u = HASH(A || B); where || is string concatenation
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateU
	(bytes AA, bytes BB)
	{
		HashFunctionPolicy hf;
		bytes aandb = AA;
		aandb.insert(aandb.end(), BB.begin(), BB.end());
		return hf.hash(aandb);
	}
	
	// S = (A *(v^u)) ^ b
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::calculateSserver
	(bytes AA, bytes verificator, bytes uu, bytes bb)
	{
		BIGNUM *A = BN_new();
		BIGNUM *v = BN_new();
		BIGNUM *u = BN_new();
		BIGNUM *b = BN_new();
		BIGNUM *tmp1 = BN_new();
		BIGNUM *tmp2 = BN_new();
		BIGNUM *S = BN_new();
		
		bytes2bignum(AA, A);
		bytes2bignum(verificator, v);
		bytes2bignum(uu, u);
		bytes2bignum(bb, b);
		
		BN_mod_exp(tmp1, v, u, N, ctx);
        BN_mod_mul(tmp2, A, tmp1, N, ctx);
        BN_mod_exp(S, tmp2, b, N, ctx);
		
		bytes result;
		bignum2bytes(S, result);
		
		BN_free(A);
		BN_free(v);
		BN_free(u);
		BN_free(b);
		BN_free(tmp1);
		BN_free(tmp2);
		BN_free(S);
		
		return result;
	}
	
	
	// true - security check passed
	// false - security check failed
	// S = (B - k*(g^x)) ^ (a + ux)
	template<class HashFunctionPolicy> 
	bool OsslMathImpl<HashFunctionPolicy>::calculateSclient
	(const bytes &BB, const bytes &xx, const bytes &aa, const bytes &uu, bytes &Sout)
	{
		// Safety SRP6a check necessary !!!!!!!!!!
		bool rval = true; // default fail
		
		BIGNUM *B = BN_new();
		BIGNUM *x = BN_new();
		BIGNUM *a = BN_new();
		BIGNUM *u = BN_new();
		BIGNUM *tmp1 = BN_new();
		BIGNUM *tmp2 = BN_new();
		BIGNUM *tmp3 = BN_new();
		BIGNUM *S = BN_new();
		
		bytes2bignum(BB, B);
		bytes2bignum(uu, u);
		
		// SRP-6a safety check
		if (!BN_is_zero(B) && !BN_is_zero(u))
		{
			bytes2bignum(xx, x);
			bytes2bignum(aa, a);
			BN_mod_mul(tmp1, u, x, N, ctx);		/* tmp1 = ux */
			BN_mod_add(tmp2, a, tmp1, N, ctx);             /* tmp2 = a+ux  */
			BN_mod_exp(tmp1, g, x, N, ctx); /* tmp1 = (g^x)%N */
			BN_mod_mul(tmp3, k, tmp1, N, ctx);             /* tmp3 = k*((g^x)%N)       */
			BN_sub(tmp1, B, tmp3);                  /* tmp1 = (B-k*((g^x)%N) */
			BN_mod_exp(S, tmp1, tmp2, N, ctx); /* S = ((B-k*((g^x)%N)^(a+ux)%N) */
			
			bignum2bytes(S, Sout);
			rval = false;
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
	
	template<class HashFunctionPolicy>
	bytes OsslMathImpl<HashFunctionPolicy>::generateRandom
	(unsigned int bits)
	{
		
	}
	
	// u = H(A || B)
	// x = H(salt || H(username || ":" || password)
	// S = (B - k*(g^x)) ^ (a + ux)
	// K = H(S)
	template<class HashFunctionPolicy>
	int OsslMathImpl<HashFunctionPolicy>::clientChallenge
	(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &S_out, bytes &M1_out)
	{
		// Safety SRP6a check necessary !!!!!!!!!!
		bool rval = true; // default fail
		
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
			
			bignum2bytes(S, S_out);
			rval = false;
		}
		
		// Calculate K
		bytes KK = hf.hash(S);
		
		// Calculate M1
		M1_out = calculateM1(username, salt, AA, BB, KK);
		
		
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
        bytes H_N = hf.hash(N);
        bytes H_g = hf.hash(g);
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
	
}
