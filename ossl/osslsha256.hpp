
#ifndef DSRP_OSSL_SHA256_HPP
#define DSRP_OSSL_SHA256_HPP

#include "dsrp/common.hpp"
#include "dsrp/hashinterface.hpp"

namespace DragonSRP
{
	class OsslSha256 : public HashInterface
	{
		public:
			~OsslSha256();
			bytes hash(const bytes &in);
			unsigned int outputLen();
	};
}


#endif
