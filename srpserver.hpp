
#ifndef DSRP_SRPSERVER_HPP
#define DSRP_SRPSERVER_HPP

#include "common.hpp"
#include "user.hpp"
#include "userlookup.hpp"
#include "hashfunction.hpp"
#include "mathfunctions.hpp"
#include "ng.hpp"

template <class HashFunctionPolicy> class HashFunction;
template <class MathFunctionsPolicy> class MathFunctions;

namespace Dsrp
{
	template<class HashFunctionPolicy, class MathFunctionsPolicy>
	class SrpServer
	{	
		public:
			// int setUsername(bytes username); // C
			// int setA(bytes AA); // A
			// UserLookup<UserLookupPolicy> getLookup();
			
		private:
			//User usr;
			bytes A;
			bytes b;
			bytes B;
			
			// UserLookup<UserLookupPolicy> ul;
			// HashFunction<HashFunctionPolicy> hf();
			MathFunctions<MathFunctionsPolicy, HashFunctionPolicy> mf();
			Ng ng();
	};
}


#endif
