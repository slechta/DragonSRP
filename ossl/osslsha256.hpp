
#ifndef OSSLSHA
#define OSSLSHA

#include "common.hpp"
#include "hashinterface.hpp"

namespace DragonSRP
{
	class OsslSha256 : public HashInterface
	{
		public:
			~OsslSha256();
			bytes hash(const bytes &in);
			unsigned int outputLen();
	};
}


#endif
