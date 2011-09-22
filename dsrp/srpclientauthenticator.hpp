
#ifndef DSRP_SRPCLIENTAUTHENTICATOR_HPP
#define DSRP_SRPCLIENTAUTHENTICATOR_HPP

#include "common.hpp"

namespace DragonSRP
{
	class SrpClientAuthenticator
	{
		friend class SrpClient; // To set K and M2_calculated
		
		public:
			SrpClientAuthenticator(const bytes &userName, const bytes &passWord, const bytes &aa, const bytes &AA);
			bytes getSessionKey(bytes M2_from_server);
		
		private:
			bytes username;
			bytes password;
			bytes a;
			bytes A;
			bytes K;
			bytes M2_calculated;
			
	};
}

#endif
