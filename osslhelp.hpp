
#ifndef DSRP_OSSLHELP_H
#define DSRP_OSSLHELP_H

#include <string>
#include <openssl/bn.h>
#include "common.hpp"

namespace Dsrp
{
	void bytes2bignum(const bytes &in, BIGNUM *out);
	void bignum2bytes(BIGNUM *in, bytes& out);
	unsigned char *bytes2array(const bytes &in, int *lenout); // return value must be deallocated with free!
	void string2bytes(const std::string &str, bytes &out);
	bytes string2bytes(const std::string &str);
	bytes string2bytes(const char *str);
}

#endif

