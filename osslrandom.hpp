
#ifndef DSRP_OSSLRANDOM_HPP
#define DSRP_OSSLRANDOM_HPP

#include "common.hpp"

namespace Dsrp
{
	class OsslRandom
	{
		protected:
			OsslRandom();
			bool getRandom(bytes &out, unsigned int len);
		private:
			FILE *fp;
			int init_ret;
	};
}

#endif
