
#include <iterator>
#include "memorylookup.hpp"
#include "user.hpp"

namespace Dsrp
{
	class User;
	
	int MemoryLookup::getByName(bytes username, User &userOut)
	{
		
		std::map<bytes, User>::iterator iter;
		iter = db.find(username);
		if (iter == db.end()) return -1;
		userOut = iter->second;
		
		
		// userOut = db[username];
		return 0;
	}
	
	int MemoryLookup::userAdd(User user)
	{
		std::map<bytes, User>::iterator iter = db.begin();
		db.insert (iter, std::pair<bytes, User>(user.getUsername(), user));  // max efficiency inserting
		return 0;
	}
}
