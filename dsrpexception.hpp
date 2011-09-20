
#ifndef DSRP_EXCEPTION_HPP
#define DSRP_EXCEPTION_HPP

#include <string>

namespace Dsrp
{
	class DsrpException
	{
		public:
			DsrpException(const char *message)
			{
				msg = std::string(message);
			}
		
			DsrpException(std::string &message)
				: msg(message)
			{
				
			}
			
			std::string what()
			{
				return msg;
			}
		
		private:
			std::string msg;
	};
	
	
}

#endif
