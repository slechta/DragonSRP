
#ifndef DSRP_RANDOMFUNC_HPP
#define DSRP_RANDOMFUNC_HPP

#include "common.hpp"

namespace Dsrp
{
	template<class RandomFunctionPolicy>
	class RandomFunction: public RandomFunctionPolicy
	{
		public:
			// returns true on success
			virtual bool getRandom(bytes &out, unsigned int len)=0;
		
	};
}


#endif
