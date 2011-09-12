
#ifndef DSRP_MATHFUNCTIONS_HPP
#define DSRP_MATHFUNCTIONS_HPP

#include "common.hpp"
#include "ng.hpp"

namespace Dsrp
{
	template<class HashFunctionPolicy>
	class MathFunctions
	{
		public:
			virtual bytes setNg(Ng<HashFunctionPolicy> ng)=0; // needs to be called first
			virtual bytes calculateA(bytes aa)=0; // a must be random
			virtual bool AisOK(bytes AA)=0; // returns !(A mod N == 0)
			virtual bytes calculateB(bytes verificator, bytes bb)=0; // b must be random
			virtual bytes calculateSserver(bytes AA, bytes verificator, bytes uu, bytes bb)=0;
			virtual bytes calculateSclient(bytes BB, bytes xx, bytes aa, bytes uu)=0;
			virtual bytes generateRandom(unsigned int bits)=0; // Maybe other class
			
		protected:	
		
		private:

	};
}

#endif
