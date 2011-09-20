
#ifndef DSRP_SRPSERVER_HPP
#define DSRP_SRPSERVER_HPP

#include "common.hpp"

#include "user.hpp"

#include "lookupinterface.hpp"
#include "hashinterface.hpp"
#include "mathinterface.hpp"
#include "randominterface.hpp"
#include "srpverificator.hpp"

#include "ng.hpp"

namespace Dsrp
{
	/* IMPORTANT: Type requirements!!!
	 * All the types must inerhit the proper interface, 
	 * for example MathPolicy must inerhit : public MathInterface
	 * otherwise you will get terrible compiler errors.
	 * 
	 * Well if only C++0x had concepts :(
	 */
	template<class LookupPolicy, class HashPolicy, class MathPolicy, class RandomPolicy>
	class SrpServer : public LookupPolicy, MathPolicy, RandomPolicy
	{	
		using LookupPolicy::getByName;
		
		public:
			SrpServer(Ng ngVal) :
				ng(ngVal)
			{
				setNg(ng);
			}			
			
			SrpVerificator getVerificator(const bytes &username, const bytes &AA)
			{
				// check status of authentification
				User usr = this->getByName(username);
				bytes M1, M2, K;
				//serverChallange(username, usr.getSalt(), usr.getVerificator(), AA, 
				
				return 0;
			}
						
			int setA(const bytes &AA) // A
			{
				// check status of authentification
				A = AA;
				return 0;
			}

			
		private:
			Ng ng;
	};
}


#endif
