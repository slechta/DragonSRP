
#include "user.hpp"

namespace Dsrp 
{	
	User::User()
	{
		
	}
	
	User::User(bytes usrname, bytes verif, bytes sal)
	{
		username = usrname;
		verificator = verif;
		salt = salt;
	}
	
	User::~User()
	{
		
	}

	User::User(const User& copy)
	{
		username = copy.username;
		salt = copy.salt;
		verificator = copy.verificator;
	}

	User & User::operator=(const User &rhs)
	{
		username = rhs.username;
		salt = rhs.salt;
		verificator = rhs.verificator;
		return *this;
	}

	bool User::operator< (const User &b)
	{
		return username < b.username;
	}

	bool User::operator() (User &a, User &b)
	{
        return a.username < b.username;
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
