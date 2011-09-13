
#ifndef DSRP_MATHFUNCTIONS_HPP
#define DSRP_MATHFUNCTIONS_HPP

#include "common.hpp"
#include "ng.hpp"

namespace Dsrp
{
	
	/* This is an iterface to class which just
	 * performs mathematical operations
	 * it doesnt check any constraints.
	 * Checking constraints is done in
	 * SrpServer and SrpClient classes
	 */  
	template<class MathFunctionsPolicy, class HashFucntionPolicy>
	class MathFunctions: public MathFunctionsPolicy
	{
		public:
			virtual bytes setNg(Ng ng)=0;
			virtual int calculateA(const bytes &aa, bytes &A_out)=0;
			virtual int clientChallenge(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &K_out, bytes &M1_out)=0;	
			virtual int serverChallange(const bytes &username, const bytes &salt, const bytes &verificator, const bytes &AA, const bytes &bb, bytes &M1_out, bytes &M2_out, bytes &K_out)=0;
			
		protected:	
		
		private:

	};
}

#endif
