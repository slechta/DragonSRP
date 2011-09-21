
#include "conversion.hpp"

namespace Dsrp
{
	void Conversion::bytes2bignum(const bytes &in, BIGNUM *out)
	{
		unsigned char *bytesIn = (unsigned char*) malloc(sizeof(unsigned char) * in.size());
		// should check if bytesIn==NULL !!!!!
		copy(in.begin(), in.end(), bytesIn);
		BN_bin2bn(bytesIn, in.size(), out);
		free(bytesIn);
	}
	
	void Conversion::bignum2bytes(BIGNUM *in, bytes& out)
	{
		unsigned char *arr = (unsigned char *) malloc(sizeof(unsigned char) * BN_num_bytes(in));
		// should check if bytesIn==NULL !!!!!
		int len = BN_bn2bin(in, arr);
		out.resize(len); // important, otherwise SIGSEGV
		copy(arr, arr + len, out.begin());
		free(arr);
	}
	
	// return value must be deallocated with free!
	unsigned char * Conversion::bytes2array(const bytes &in, int *lenout)
	{
		unsigned char *arr = (unsigned char*) malloc(sizeof(unsigned char) * in.size());
		// should check if bytesIn==NULL !!!!!
		copy(in.begin(), in.end(), arr);
		*lenout = in.size();
		return arr;
	}
	
	bytes Conversion::array2bytes(const unsigned char *in, int len)
	{
		bytes ret;
		ret.resize(len);
		copy(in, in + len, ret.begin());
		return ret;
	}
	
	// returns without \0
	void Conversion::string2bytes(const std::string &str, bytes &out)
	{
		const char *s = str.c_str();
		out.resize(str.size()); // important, otherwise SIGSEGV
		copy(s, s + str.size(), out.begin());
	}
	
	// returns without \0
	bytes Conversion::string2bytes(const std::string &str)
	{
		bytes out;
		const char *s = str.c_str();
		out.resize(str.size()); // important, otherwise SIGSEGV
		copy(s, s + str.size(), out.begin());
		return out;
	}
	
	// returns without \0
	bytes Conversion::string2bytes(const char *str)
	{
		bytes out;
		out.resize(strlen(str)); // important, otherwise SIGSEGV
		copy(str, str + strlen(str), out.begin());
		return out;
	}
	
	/*
	bytes Conversion::hexstring2bytes(const char *str) // throws conversion exception
	{
		
	}
	*/
}
