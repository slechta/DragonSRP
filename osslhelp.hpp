
#ifndef DSRP_OSSLHELP_H
#define DSRP_OSSLHELP_H

#include <openssl/bn.h>
#include "common.hpp"

namespace Dsrp
{
	void bytes2bignum(const bytes &in, BIGNUM *out);
}

#endif

