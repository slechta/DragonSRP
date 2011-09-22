
#ifndef DSRP_OSSL_SHA1_HPP
#define DSRP_OSSL_SHA1_HPP

#include "dsrp/common.hpp"
#include "dsrp/hashinterface.hpp"

namespace DragonSRP
{
	class OsslSha1 : public HashInterface
	{
		public:
			~OsslSha1();
			bytes hash(const bytes &in);
			unsigned int outputLen();
	};
}


#endif
