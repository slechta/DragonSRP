

#include "srpclient.hpp"

namespace DragonSRP
{
	SrpClient::SrpClient(MathInterface &mathInterface, RandomInterface &randomInterface) :
		math(mathInterface),
		random(randomInterface)
	{
			
	}
	
	SrpClientAuthenticator SrpClient::getAuthenticator(bytes username, bytes password)
	{
		bytes a = random.getRandom(32); // WTF? dont know how much, throws on error
		bytes A = math.calculateA(a);
		return SrpClientAuthenticator(username, password, a, A);
	}
	
	bytes SrpClient::getM1(bytes salt, bytes B, SrpClientAuthenticator &sca)
	{
		bytes M1, M2, K;
		math.clientChallange(salt, sca.a, sca.A, B, sca.username, sca.password, M1, M2, K);
		sca.M2_calculated = M2;
		sca.K = K;
		return M1;
	}
}
