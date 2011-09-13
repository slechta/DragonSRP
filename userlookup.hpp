
#ifndef DSRP_USERLOOKUP_HPP
#define DSRP_USERLOOKUP_HPP

#include "common.hpp"
#include "user.hpp"

namespace Dsrp
{
	template<class UserLookupPolicy>
	class UserLookup : public UserLookupPolicy
	{
		virtual int getByName(bytes username, bytes &userOut)=0; // returns 0 on success
	};
	
}

#endif
