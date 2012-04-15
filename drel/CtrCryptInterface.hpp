// Dragon Encryption Layer

#ifndef DREL_CTRCRYPTINTERFACE_HPP
#define DREL_CTRCRYPTINTERFACE_HPP

#define DREL_AES_BLOCKLEN_BYTES 16
#define DREL_AES_SALTLEN 7
#define DREL_AES_IVLEN 8
#define DREL_AES_PALEN 1

#define DREL_AES_KEYLEN 32

// ( (DREL_AES_KEYLEN * DREL_AES_BLOCKLEN_BYTES) - 1)
#define DREL_AES_MAXPACKETOCT 4095

#include <sys/types.h>
#include <inttypes.h>

#include "aes/aes.h"


namespace DragonEncryptionLayer
{
	
	class CtrCryptInterface
	{
		public:
			~CtrCryptInterface() = 0;
	
			virtual void encrypt(unsigned char *datain, unsigned char *dataout, int len) = 0;			
			virtual unsigned int getEncKeyLen() = 0;
			virtual unsigned int getIvLen() = 0;
			virtual unsigned int getMaxPacketLen() = 0;
			virtual unsigned int getSaltLen() = 0;
		
	};
}
#endif

