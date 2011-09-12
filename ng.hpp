
#ifndef DSRP_NG_HPP
#define DSRP_NG_HPP

#include "common.hpp"
#include "hashfunction.hpp"

namespace Dsrp
{
	template<class HashFunctionPolicy>
	class Ng: public HashFunctionPolicy
	{
		public:
			Ng(bytes NN, bytes gg);
			Ng(Ng& copy);
			bytes getN();
			bytes getg();
			bytes getk();
			static Ng predefined(unsigned int bits);
			// checkNg();
		private:
			void calculateMultiplier();
			bytes N, g, k;
	};
}

#endif
