
#ifndef OSSLSHA
#define OSSLSHA

#include "common.hpp"
#include "hashinterface.hpp"

namespace Dsrp
{
	class OsslSha256 : public HashInterface
	{
		public:
			bytes hash(const bytes &in);
			unsigned int outputLen();
	};
}


#endif
