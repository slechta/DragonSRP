
#include "srpclientauthenticator.hpp"
#include "dsrpexception.hpp"

namespace DragonSRP
{
	SrpClientAuthenticator::SrpClientAuthenticator(const bytes &userName, 
				const bytes &passWord, const bytes &aa, const bytes &AA) :
			username(userName),
			password(passWord),
			a(aa),
			A(AA)
		
	{
		
	}
	
	bytes SrpClientAuthenticator::getSessionKey(bytes M2_from_server)
	{
		if (M2_from_server != M2_calculated) throw DsrpException("Authentification failed, bad password");
		return K;
	}
	
	bytes SrpClientAuthenticator::getA()
	{
		return A;
	}
}
