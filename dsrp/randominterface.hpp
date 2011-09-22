
#ifndef DSRP_RANDOMINTERFACE_HPP
#define DSRP_RANDOMINTERFACE_HPP

#include "common.hpp"

namespace DragonSRP
{
	class RandomInterface
	{
		public:
			// returns true on success
			virtual ~RandomInterface()=0; // throws on error
			virtual bytes getRandom(unsigned int lenBytes)=0; // throws on error
		
	};
}


#endif
