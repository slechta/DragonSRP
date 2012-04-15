// Dragon Encryption Layer

#ifndef DREL_DATAGRAMENCRYPTOR_HPP
#define DREL_DATAGRAMDECRYPTOR_HPP

#include <sys/types.h>
#include <inttypes.h>

#include "../hmac/hmac.hpp"
#include "aescounter.hpp"

#include "simplekeyderivator.hpp"
// *--2-----8------------------12---*
// | LEN | SEQ | ENC(DATA) | DIGEST |
// *--------------------------------*
//             <--ENCRYPT-->
// <-----AUTHENTICATE------>

// LEN = sizeof(ENCRYPT(DATA))
// First encrypt and then the encrypted with associated data authenticate

namespace DragonEncryptionLayer
{	
	class DatagramEncryptor
	{	
		public:
			DatagramEncryptor(const bytes &encryptionKey, const bytes &IV, const bytes &macKey);
			void encryptAndAuthenticate(const bytes &in, bytes &out);
			
		private:	
			AesCounter aesCtr;
			OsslSha1 sha1;
			Hmac hmac;
	};
}
#endif

