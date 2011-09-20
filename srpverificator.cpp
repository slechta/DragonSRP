
#include "srpverificator.hpp"

namespace Dsrp
{
	SrpVerificator::SrpVerificator(bytes userName, bytes userSalt, bytes B, bytes calculated_M1, bytes calculated_M2)
		: salt(userSalt),
		BB(B),
		calc_M1(calculated_M1), 
		calc_M2(calculated_M2),
		username(userName)			  
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
}
