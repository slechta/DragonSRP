
#ifndef DSRP_LOOKUPINTERFACE_HPP
#define DSRP_LOOKUPINTERFACE_HPP

#include "common.hpp"
#include "user.hpp"

namespace Dsrp
{
	class LookupInterface
	{
		public:
			virtual bool getByName(bytes username, User &userOut)=0; // returns true on success
	};
	
}

#endif
