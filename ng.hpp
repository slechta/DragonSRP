
#ifndef DSRP_NG_HPP
#define DSRP_NG_HPP

#include "common.hpp"

namespace Dsrp
{
	class Ng
	{
		public:
			Ng(bytes NN, bytes gg);
			// Ng(const Ng& copy); // Copy constructor for STL Vector
			bytes getN();
			bytes getg();
			static Ng predefined(unsigned int bitlen);
			// checkNg();
		private:
			bytes N, g;
	};
}

#endif
