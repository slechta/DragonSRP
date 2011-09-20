
#ifndef DSRP_LOOKUPINTERFACE_HPP
#define DSRP_LOOKUPINTERFACE_HPP

#include "common.hpp"
#include "user.hpp"

namespace Dsrp
{
	class LookupInterface
	{
		public:
			virtual User getByName(bytes username)=0; // throws if user not found
	};
	
}

#endif
