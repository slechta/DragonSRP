
#ifndef DSRP_NG_HPP
#define DSRP_NG_HPP

#include "common.hpp"
#include "hashfunction.hpp"

namespace Dsrp
{
	class Ng
	{
		public:
			Ng(bytes NN, bytes gg);
			Ng(Ng& copy);
			bytes getN();
			bytes getg();
			// checkNg();
		private:
			bytes N, g;
	};
}

#endif
