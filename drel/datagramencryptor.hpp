// Dragon Encryption Layer

#ifndef DREL_DATAGRAMENCRYPTOR_HPP
#define DREL_DATAGRAMENCRYPTOR_HPP

#include <sys/types.h>
#include <inttypes.h>

#include "../mac/hmac.hpp"
#include "../dsrp/common.hpp"
#include "../dsrp/dsrpexception.hpp"
#include "../dsrp/hashinterface.hpp"
#include "../ossl/osslsha1.hpp"
#include "aescounter.hpp"
#include "encparams.hpp"
#include "simplekeyderivator.hpp"


// *--2-----8------------------12---*
// | LEN | SEQ | ENC(DATA) | DIGEST |
// *--------------------------------*
//             <--ENCRYPT-->
// <-----AUTHENTICATE------>

// LEN = sizeof(ENCRYPT(DATA))
// First encrypt and then the encrypted with associated data authenticate

namespace DragonSRP
{	
	class DatagramEncryptor
	{	
		public:
			DatagramEncryptor(const bytes &encryptionKey, const bytes &IV, const bytes &macKey);
			void encryptAndAuthenticate(const unsigned char *plaintext, unsigned int plaintextLen, unsigned char *out, unsigned int *outLen); // throws
			unsigned int getOverheadLen();
			
		private:	
			AesCounter aesCtr;
			OsslSha1 sha1;
			Hmac hmac;
	};
}
#endif

