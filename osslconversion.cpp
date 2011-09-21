
#include "osslconversion.hpp"

namespace DragonSRP
{
	void OsslConversion::bytes2bignum(const bytes &in, BIGNUM *out)
	{
		unsigned char *bytesIn = (unsigned char*) malloc(sizeof(unsigned char) * in.size());
		// should check if bytesIn==NULL !!!!!
		copy(in.begin(), in.end(), bytesIn);
		BN_bin2bn(bytesIn, in.size(), out);
		free(bytesIn);
	}
	
	void OsslConversion::bignum2bytes(BIGNUM *in, bytes& out)
	{
		unsigned char *arr = (unsigned char *) malloc(sizeof(unsigned char) * BN_num_bytes(in));
		// should check if bytesIn==NULL !!!!!
		int len = BN_bn2bin(in, arr);
		out.resize(len); // important, otherwise SIGSEGV
		copy(arr, arr + len, out.begin());
		free(arr);
	}
}
