
#ifndef DSRP_OSSLRANDOM_HPP
#define DSRP_OSSLRANDOM_HPP

#include "common.hpp"

namespace Dsrp
{
	class OsslRandom
	{
		protected:
			OsslRandom();
			bytes getRandom(unsigned int len);
		private:
			FILE *fp;
			int init_ret;
	};
}

#endif
