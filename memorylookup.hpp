
#ifndef DSRP_MEMORYLOOKUP_HPP
#define DSRP_MEMORYLOOKUP_HPP

#include <map>
#include "common.hpp"
#include "lookupinterface.hpp"
#include "user.hpp"

namespace Dsrp
{
	class MemoryLookup : public LookupInterface
	{
		public:
			bool getByName(bytes username, User &userOut); // returns true on success
			bool userAdd(User user); // returns true on success
			
		private:
			std::map<bytes, User> db;
	};
}

#endif
