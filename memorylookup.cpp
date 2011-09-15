
#include <iterator>
#include "memorylookup.hpp"
#include "user.hpp"

namespace Dsrp
{
	class User;
	
	bool MemoryLookup::getByName(bytes username, User &userOut)
	{
		std::map<bytes, User>::iterator iter;
		iter = db.find(username);
		if (iter == db.end()) return false;
		userOut = iter->second;
		return 0;
	}
	
	bool MemoryLookup::userAdd(User user)
	{
		std::pair<std::map<bytes, User>::iterator, bool> ret = db.insert(make_pair(user.getUsername(), user));
		return ret.second;
	}
}
