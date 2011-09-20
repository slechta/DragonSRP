
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
			SrpVerificator(bytes userName, bytes userSalt, bytes B, bytes calculated_M1, bytes calculated_M2)
				: salt(userSalt),
				  BB(B),
				  calc_M1(calculated_M1), 
				  calc_M2(calculated_M2),
				  username(userName)
				  
			{
				
			}
		
			bytes getSalt()
			{
				return salt;
			}
			
			bytes getB()
			{
				return BB;
			}
		
			bytes getUsername()
			{
				return username;
			}
		
		/*
			void authenticate(const bytes &M1_from_client, bytes &M2_to_client, bytes &session_K)
			{
				if (calc_M1 != M1_from_client) throw DsrpException("Authentification failed; possibly wrong password");
								
			}
		*/
			
		
			
		private:
			bytes salt;
			bytes BB;
			bytes calc_M1;
			bytes calc_M2;
			bytes KK;
			bytes username;
			
		/*
			bytes A;
			bytes b;
			bytes B;
			
		*/
	};
	
}

#endif
