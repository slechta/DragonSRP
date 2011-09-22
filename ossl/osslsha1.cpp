

#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

#include "osslsha1.hpp"
#include "dsrp/conversion.hpp"

namespace DragonSRP
{
	OsslSha1::~OsslSha1()
	{
		// empty
	}
	
	bytes OsslSha1::hash(const bytes &in)
	{
		int len;
		unsigned char *arr = Conversion::bytes2array(in, &len);
	
		SHA_CTX context;
		unsigned char md[SHA_DIGEST_LENGTH];
		
		SHA1_Init(&context);
		SHA1_Update(&context, arr, len);
		SHA1_Final(md, &context);
		
		bytes ret = Conversion::array2bytes(arr, SHA_DIGEST_LENGTH);
		
		free(arr);
		return ret;
	}
	
	unsigned int OsslSha1::outputLen()
	{
		return SHA_DIGEST_LENGTH;
	}
}
