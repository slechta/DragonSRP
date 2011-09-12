
#ifndef DSRP_USERLOOKUP_HPP
#define DSRP_USERLOOKUP_HPP

#include "common.hpp"
#include "user.hpp"

namespace Dsrp
{
	class UserLookup
	{
		virtual User getByName(bytes username)=0;
	};
	
}

#endif
