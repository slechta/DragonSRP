
#ifndef DSRP_RANDOMINTERFACE_HPP
#define DSRP_RANDOMINTERFACE_HPP

#include "common.hpp"

namespace Dsrp
{
	class RandomInterface
	{
		public:
			// returns true on success
			virtual ~RandomInterface()=0;
			virtual bool getRandom(bytes &out, unsigned int len)=0;
		
	};
}


#endif
