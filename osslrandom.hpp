
#ifndef DSRP_OSSLRANDOM_HPP
#define DSRP_OSSLRANDOM_HPP

#include "common.hpp"
#include "randominterface.hpp"

namespace Dsrp
{
	class OsslRandom : public RandomInterface
	{
		public:
			OsslRandom();
			bool getRandom(bytes &out, unsigned int len);
		private:
			FILE *fp;
			int init_ret;
	};
}

#endif
