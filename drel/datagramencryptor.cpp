
#include <string.h>

#include "datagramencryptor.hpp"

namespace DragonEncryptionLayer
{

	DatagramEncryptor::DatagramEncryptor(const bytes &encryptionKey, const bytes &IV, const bytes &macKey) :
		hmac(hash, macKey),
		aesCtr(&IV[0], IV.size(), &encryptionKey[0], encryptionKey.size())
	{
		if (macKey.size() < hash.outputLen()) throw DsrpException("DatagramEncryptor::DatagramEncryptor: macKey not long enough");
		
	}
	
	void DatagramEncryptor::encryptAndAuthenticate(const bytes &in, bytes &out)
	{
		out.clear();
			
		const unsigned int lenSize = 2;
		const unsigned int seqSize = 8;
		const unsigned int digestSize = 12;
		
		uint16_t dataLen = in.size();
		uint64_t seqNum;
		
		unsigned int datagramlen = lenSize + seqSize + in.size() + digestSize; // len field is of size 2; 12 = digest length
		
		out.resize(datagramlen); // maybe reserve() should be ok
		
		// in -----encrypt-----> encdata
		// ---> seqNum
		aesCtr.encrypt(&in[0], &out[lenSize + seqSize], in.size(), &seqNum); // Possible optim. direct to &out[lenSize + seqSize]
		
		memcpy(&out[0], dataLen, 2)
		memcpy(&out[lenSize], &seqNum, seqSize);
		
		bytes digest;
 		hmac.hmac(out, digest); // sign(len + seq + encrypt(in))
 		digest.resize(digestSize); // truncate
 		Conversion::append(out, digest);
	}


}
