
#ifndef DSRP_OSSLRANDOM_HPP
#define DSRP_OSSLRANDOM_HPP

#include "dsrp/common.hpp"
#include "dsrp/randominterface.hpp"
#include "dsrp/dsrpexception.hpp"

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
