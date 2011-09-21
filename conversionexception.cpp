
#include "conversionexception.hpp"

namespace DragonSRP
{
	ConversionException::ConversionException(const char *message, const bytes &userName) :
		DsrpException(message),
		username(userName)
	{
		
	}
	
	ConversionException::ConversionException(std::string &message, const bytes &userName) :
		DsrpException(message),
		username(userName)
	{
		
	}
}
