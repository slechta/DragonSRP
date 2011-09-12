
#ifndef DSRP_USER_HPP
#define DSRP_USER_HPP

#include "common.hpp"

namespace Dsrp
{
	class User
	{
		public:
			User(bytes username, bytes verificator, bytes salt);
			User(User& copy);
			bytes getUsername();
			bytes getVerificator();
			bytes getSalt();
		
		private:
			bytes username, verificator, salt;
	};
}

#endif
