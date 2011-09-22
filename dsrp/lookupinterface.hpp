
#ifndef DSRP_LOOKUPINTERFACE_HPP
#define DSRP_LOOKUPINTERFACE_HPP

#include "common.hpp"
#include "user.hpp"

namespace DragonSRP
{
	class LookupInterface
	{
		public:
			virtual ~LookupInterface()=0;
			virtual User getByName(bytes username)=0; // throws if user not found
	};
}

#endif
