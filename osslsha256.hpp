
#ifndef OSSLSHA
#define OSSLSHA

#include "common.hpp"
#include "hashinterface.hpp"

namespace Dsrp
{
	class OsslSha256 : public HashInterface
	{
		protected:
			bytes hash(const bytes &in);
			unsigned int ouputLen();
		private:
	};
}


#endif
