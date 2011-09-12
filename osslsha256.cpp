

#include <stdlib.h>
#include <openssl/sha.h>
#include "osslsha256.hpp"
#include "osslhelp.hpp"

namespace Dsrp
{
	bytes OsslSha256::hash(bytes in)
	{
		int len;
		unsigned char *arr = bytes2array(in, &len);
	
		SHA256_CTX context;
		unsigned char md[SHA256_DIGEST_LENGTH];
		
		SHA256_Init(&context);
		SHA256_Update(&context, arr, len);
		SHA256_Final(md, &context);
		
		bytes ret;
		copy(arr, arr + SHA256_DIGEST_LENGTH, ret.begin());
		free(arr);
		return ret;
	}
}
