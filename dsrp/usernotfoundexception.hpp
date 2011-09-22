
#ifndef DSRP_USERNOTFOUNDEXCEPTION_HPP
#define DSRP_USERNOTFOUNDEXCEPTION_HPP

#include "common.hpp"
#include "dsrpexception.hpp"

namespace DragonSRP
{
	class UserNotFoundException : public DsrpException
	{
		public:
			UserNotFoundException(const char *message, const bytes &userName);
			UserNotFoundException(std::string &message, const bytes &userName);
			bytes getUsername();
		
		private:
			bytes username;
	};
	
}

#endif
