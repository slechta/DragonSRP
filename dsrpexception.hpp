
#ifndef DSRP_EXCEPTION_HPP
#define DSRP_EXCEPTION_HPP

#include <string>

namespace DragonSRP
{
	class DsrpException
	{
		public:
			DsrpException(const char *message);
			DsrpException(std::string &message);
			std::string what();
					
		private:
			std::string msg;
	};
	
	
}

#endif
