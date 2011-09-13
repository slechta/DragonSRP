
#ifndef OSSLSHA
#define OSSLSHA

#include "common.hpp"

namespace Dsrp
{
	class OsslSha256 // zdedit asi fakt ne
	{
		protected:
			bytes hash(const bytes &in);
			unsigned int ouputLen();
		private:
	};
}


#endif
