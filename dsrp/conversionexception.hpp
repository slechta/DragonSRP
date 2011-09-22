
#ifndef DSRP_CONVERSIONEXCEPTION_HPP
#define DSRP_CONVERSIONEXCEPTION_HPP

#include "common.hpp"
#include "dsrpexception.hpp"

namespace DragonSRP
{
	class ConversionException : public DsrpException
	{
		public:
			ConversionException(const char *message);
			ConversionException(std::string &message);
	};
	
}

#endif
