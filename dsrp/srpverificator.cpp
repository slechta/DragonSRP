
#include "srpverificator.hpp"

namespace DragonSRP
{
	SrpVerificator::SrpVerificator(bytes userName, bytes userSalt, bytes B, bytes calculated_M1, bytes calculated_M2, bytes K)
		: salt(userSalt),
		BB(B),
		calc_M1(calculated_M1), 
		calc_M2(calculated_M2),
		username(userName),
		KK(K)
	{
				
	}
	
	bytes SrpVerificator::getSalt()
	{
		return salt;
	}
	
	bytes SrpVerificator::getB()
	{
		return BB;
	}
	
	bytes SrpVerificator::getUsername()
	{
		return username;
	}
	

	void SrpVerificator::authenticate(const bytes &M1_from_client, bytes &M2_to_client, bytes &session_K)
	{
		if (calc_M1 != M1_from_client) throw DsrpException("Authentification failed; possibly wrong password");
		M2_to_client = calc_M2;
		session_K = KK;
	}

}
