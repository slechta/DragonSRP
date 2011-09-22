
#include "srpserver.hpp"

namespace DragonSRP
{
	
	SrpServer::SrpServer(LookupInterface &lookupInterface, MathInterface &mathInterface, RandomInterface &randomInterface) :
		lookup(lookupInterface),
		math(mathInterface),
		random(randomInterface)
	{
			
	}	
	
	SrpVerificator SrpServer::getVerificator(const bytes &username, const bytes &AA)
	{
		// check status of authentification
		User usr = lookup.getByName(username); // throws if not found
		bytes M1, M2, K, B;
		bytes b = random.getRandom(32); // WTF? dont know how much, throws on error
		math.serverChallange(username, usr.getSalt(), usr.getVerificator(), AA, b, B, M1, M2, K); // throws on error
		return SrpVerificator(username, usr.getSalt(), B, M1, M2, K);
	}
			
	
	
}
