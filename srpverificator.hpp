
#ifndef DSRP_SRPVERIFICATOR_HPP
#define DSRP_SRPVERIFICATOR_HPP

#include "common.hpp"
#include "user.hpp"
#include "dsrpexception.hpp"

namespace Dsrp
{
	class SrpVerificator
	{
		public:
			SrpVerificator(bytes userName, bytes userSalt, bytes B, bytes calculated_M1, bytes calculated_M2, bytes K);
			bytes getSalt();
			bytes getB();
			bytes getUsername();
			void authenticate(const bytes &M1_from_client, bytes &M2_to_client, bytes &session_K);
					
		private:
			bytes salt;
			bytes BB;
			bytes calc_M1;
			bytes calc_M2;
			bytes KK; // session key
			bytes username;
	};
	
}

#endif
