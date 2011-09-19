

#ifndef DSRP_HASHINTERFACE_HPP
#define DSRP_HASHINTERFACE_HPP

#include "common.hpp"

namespace Dsrp
{
	class HashInterface
	{
		public:
			virtual bytes hash(const bytes &in)=0;
			virtual unsigned int ouputLen()=0;
	};
}

#endif
