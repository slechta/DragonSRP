
#ifndef DSRP_CONVERSIONEXCEPTION_HPP
#define DSRP_CONVERSIONEXCEPTION_HPP

#include "common.hpp"
#include "dsrpexception.hpp"

namespace Dsrp
{
	class ConversionException : public DsrpException
	{
		public:
			ConversionException(const char *message, const bytes &userName);
			ConversionException(std::string &message, const bytes &userName);
		
		private:
			bytes username;
	};
	
}

#endif
