

#include "dsrpexception.hpp"

namespace DragonSRP
{
	DsrpException::DsrpException(const char *message)
	{
		msg = std::string(message);
	}
	
	DsrpException::DsrpException(std::string &message)
		: msg(message)
	{
				
	}	
	
	std::string DsrpException::what()
	{
		return msg;
	}
}
