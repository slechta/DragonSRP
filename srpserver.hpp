
#ifndef DSRP_SRPSERVER_HPP
#define DSRP_SRPSERVER_HPP

#include "common.hpp"

#include "user.hpp"

#include "lookupinterface.hpp"
#include "hashinterface.hpp"
#include "mathinterface.hpp"
#include "randominterface.hpp"

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
		public:
			SrpServer(Ng ngVal) :
				ng(ngVal)
			{
				
			}			
			
			int setUsername(bytes username) // C
			{
				// check status of authentification
				// usr = ul.getByName(username);
				return 0;
			}
						
			int setA(bytes AA) // A
			{
				// check status of authentification
				A = AA;
				return 0;
			}

			
		private:
			//User usr;
			bytes A;
			bytes b;
			bytes B;
			Ng ng;
	};
}


#endif
