

#ifndef DSRP_HASHFUNCTION_HPP
#define DSRP_HASHFUNCTION_HPP

#include "common.hpp"

namespace Dsrp
{
	// Just an interface
	class HashFucntion
	{
		public:
			virtual bytes hash(bytes)=0;
			virtual unsigned int ouputLen()=0;
		protected:
		
		private:
			bytes calculateM1(bytes A, bytes B, bytes S);
			bytes calculateM2(bytes A, bytes M1, bytes S);
	};
}

#endif
