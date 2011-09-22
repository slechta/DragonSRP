
#ifndef DSRP_OSSLRANDOM_HPP
#define DSRP_OSSLRANDOM_HPP

#include "common.hpp"
#include "randominterface.hpp"
#include "dsrpexception.hpp"

namespace DragonSRP
{
	class OsslRandom : public RandomInterface
	{
		public:
			OsslRandom();
			bytes getRandom(unsigned int lenBytes);
		private:
			FILE *fp;
			bool initOk;
	};
}

#endif
