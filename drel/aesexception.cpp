
#include "aesexception.hpp"


namespace DragonEncryptionLayer
{
	AesException::AesException(const char *message) :
		msg(message)
	{
		
	}
	
	AesException::AesException(std::string &message) :
		msg(message)
	{
		
	}
	
	std::string AesException::what()
	{
		return msg;
	}
}
