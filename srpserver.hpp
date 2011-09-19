
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
	template<class LookupPolicy, class HashPolicy, class RandomPolicy>
	class SrpServer : public LookupPolicy, HashPolicy, RandomPolicy
	{	
		public:
			//SrpServer(UserLookup<UserLookupPolicy> &userLookup);
			// int setUsername(bytes username); // C
			// int setA(bytes AA); // A
			// UserLookup<UserLookupPolicy> getLookup();
			
		private:
			//User usr;
			bytes A;
			bytes b;
			bytes B;
			
			
			// UserLookup<UserLookupPolicy> ul();
			// MathFunctions<MathFunctionsPolicy, HashFunctionPolicy> mf();
			
			Ng ng();
	};
}


#endif
