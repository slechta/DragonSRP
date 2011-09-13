
#ifndef DSRP_USER_HPP
#define DSRP_USER_HPP

#include "common.hpp"

namespace Dsrp
{
	class User
	{
		public:
			User(bytes username, bytes verificator, bytes salt);
			~User();
			
			User();
			User(const User &copy); // Copy constructor
			User & operator=(const User &rhs); // Assignment operator

			bool operator() (User &a, User &b); // less <T>
			bool operator< (const User &b); // Copmarator
			
			
			
			bytes getUsername();
			bytes getVerificator();
			bytes getSalt();
		private:
			bytes username, verificator, salt;
	};
}

#endif
