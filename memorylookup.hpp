
#ifndef DSRP_MEMORYLOOKUP_HPP
#define DSRP_MEMORYLOOKUP_HPP

#include <map>
#include "common.hpp"
#include "user.hpp"

namespace Dsrp
{
	class MemoryLookup
	{
		public:
			int getByName(bytes username, User &userOut); // returns 0 on success
			int userAdd(User user);
			
		private:
			std::map<bytes, User> db;
	};
}

#endif
