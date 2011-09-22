
#ifndef DSRP_SRPCLIENT_HPP
#define DSRP_SRPCLIENT_HPP

#include "common.hpp"

#include "mathinterface.hpp"
#include "randominterface.hpp"

#include "srpclientauthenticator.hpp"

namespace DragonSRP
{	
	class SrpClient
	{		
		public:
			SrpClient(MathInterface &mathInterface, RandomInterface &randomInterface);
			SrpClientAuthenticator getAuthenticator(bytes username, bytes password);
			bytes getM1(bytes salt, bytes B, SrpClientAuthenticator &sca);

		private:
			MathInterface &math;
			RandomInterface &random;	
	};
}

#endif
