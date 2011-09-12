
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
			virtual bytes calculateA(bytes a)=0; // a must be random
			virtual bytes calculateB(bytes verificator, bytes b)=0; // b must be random
			virtual bytes calculateSserver(bytes A, bytes verificator, bytes u, bytes b)=0;
			virtual bytes calculateSclient(bytes B, bytes x, bytes a, bytes u)=0;
			virtual bytes generateRandom(unsigned int bits)=0; // Maybe other class
			
		protected:	
		
		private:

	};
}

#endif
