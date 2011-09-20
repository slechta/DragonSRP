

#include <stdio.h>
#include <iterator>
#include "memorylookup.hpp"
#include "user.hpp"
#include "dsrpexception.hpp"

namespace Dsrp
{
	class User;
	
	User MemoryLookup::getByName(bytes username)
	{
		printf("ble ble ble \n");
		std::map<bytes, User>::iterator iter;
		iter = db.find(username);
		if (iter == db.end()) throw DsrpException("User not found.");
		return iter->second;
	}
	
	bool MemoryLookup::userAdd(User user)
	{
		std::pair<std::map<bytes, User>::iterator, bool> ret = db.insert(make_pair(user.getUsername(), user));
		return ret.second;
	}
}
