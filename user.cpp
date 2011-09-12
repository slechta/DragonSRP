
#include "user.hpp"

namespace Dsrp 
{	
	User::User(bytes usrname, bytes verif, bytes sal)
	{
		username = usrname;
		verificator = verif;
		salt = salt;
	}

	User::User(User& copy)
	{
		copy.username = username;
		copy.salt = salt;
		copy.verificator = verificator;
	}

	bytes User::getUsername()
	{
		return username;
	}

	bytes User::getVerificator()
	{
		return verificator;
	}

	bytes User::getSalt()
	{
		return salt;
	}
}
