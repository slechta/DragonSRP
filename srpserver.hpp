
#ifndef DSRP_SRPSERVER_HPP
#define DSRP_SRPSERVER_HPP

#include "common.hpp"
#include "ng.hpp"
#include "userlookup.hpp"
#include "mathfunctions.hpp"
#include "user.hpp"

namespace Dsrp
{
	template<class UserLookupPolicy, class HashFunctionPolicy, class MathFunctionsPolicy>
	class SrpServer
	{	
		public:
			int setUsername(bytes username); // C
			int setA(bytes A); // A
			
		private:
			User usr;
			bytes A;
			bytes b;
			bytes B;
			
			UserLookupPolicy ul;
			HashFunctionPolicy hf;
			MathFunctionsPolicy mf;
			Ng<HashFunctionPolicy> ng;
	};
	
	
}


#endif
