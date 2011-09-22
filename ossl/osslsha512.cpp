

#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

#include "osslsha512.hpp"
#include "conversion.hpp"

namespace DragonSRP
{
	OsslSha512::~OsslSha512()
	{
		// empty
	}
	
	bytes OsslSha512::hash(const bytes &in)
	{
		int len;
		unsigned char *arr = Conversion::bytes2array(in, &len);
	
		SHA512_CTX context;
		unsigned char md[SHA512_DIGEST_LENGTH];
		
		SHA512_Init(&context);
		SHA512_Update(&context, arr, len);
		SHA512_Final(md, &context);
		
		bytes ret = Conversion::array2bytes(arr, SHA512_DIGEST_LENGTH);
		
		free(arr);
		return ret;
	}
	
	unsigned int OsslSha512::outputLen()
	{
		return SHA512_DIGEST_LENGTH;
	}
}
