#ifndef DREL_AESEXCEPTION_HPP
#define DREL_AESEXCEPTION_HPP

#include <string>

namespace DragonEncryptionLayer
{
	class AesException
	{
		public:
			AesException(const char *message);
			AesException(std::string &message);
			std::string what();
					
		private:
			std::string msg;
	};
	
}

#endif
