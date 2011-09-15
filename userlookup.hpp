
#ifndef DSRP_USERLOOKUP_HPP
#define DSRP_USERLOOKUP_HPP

#include "common.hpp"
#include "user.hpp"

namespace Dsrp
{
	template<class UserLookupPolicy>
	class UserLookup : public UserLookupPolicy
	{
		virtual bool getByName(bytes username, bytes &userOut)=0; // returns true on success
	};
	
}

#endif
