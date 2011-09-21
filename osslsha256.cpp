

#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

#include "osslsha256.hpp"
#include "conversion.hpp"

namespace Dsrp
{
	OsslSha256::~OsslSha256()
	{
		// empty
	}
	
	bytes OsslSha256::hash(const bytes &in)
	{
		int len;
		unsigned char *arr = Conversion::bytes2array(in, &len);
	
		SHA256_CTX context;
		unsigned char md[SHA256_DIGEST_LENGTH];
		
		SHA256_Init(&context);
		SHA256_Update(&context, arr, len);
		SHA256_Final(md, &context);
		
		bytes ret = Conversion::array2bytes(arr, SHA256_DIGEST_LENGTH);
		
		free(arr);
		return ret;
	}
	
	unsigned int OsslSha256::outputLen()
	{
		return SHA256_DIGEST_LENGTH;
	}
}
