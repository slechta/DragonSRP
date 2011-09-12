
#ifndef DSRP_OSSLHELP_H
#define DSRP_OSSLHELP_H

#include <openssl/bn.h>
#include "common.hpp"

namespace Dsrp
{
	void bytes2bignum(const bytes &in, BIGNUM *out);
	void bignum2bytes(BIGNUM *in, bytes& out);
	unsigned char *bytes2array(const bytes &in, int *lenout); // return value must be deallocated with free!
}

#endif

