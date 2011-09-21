
#include "conversionexception.hpp"

namespace DragonSRP
{
	ConversionException::ConversionException(const char *message) :
		DsrpException(message)
	{
		
	}
	
	ConversionException::ConversionException(std::string &message) :
		DsrpException(message)
	{
		
	}
}
