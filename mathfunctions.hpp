
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
	template<class HashFunctionPolicy>
	class MathFunctions
	{
		public:
			virtual bytes setNg(Ng ng)=0; // needs to be called first
			
			// virtual bytes calculateA(const bytes &aa)=0; // a must be random
			
			virtual bool AisOK(bytes AA)=0; // returns !(A mod N == 0)
			
			virtual bytes calculateB(bytes verificator, bytes bb)=0; // b must be random
			virtual bytes calculateU(bytes AA, bytes BB);
			virtual bytes calculateSserver(bytes AA, bytes verificator, bytes uu, bytes bb)=0;
			
			virtual int clientChallenge(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &S_out, bytes &M1_out)=0;
			
			virtual bytes generateRandom(unsigned int bits)=0; // Maybe other class
			
		protected:	
		
		private:

	};
}

#endif
