
#include <string.h>

#include "datagramdecryptor.hpp"

namespace DragonEncryptionLayer
{

	DatagramDecryptor::DatagramDecryptor(const bytes &encryptionKey, const bytes &IV, const bytes &macKey) :
		hmac(hash, macKey),
		aesCtr(&IV[0], IV.size(), &encryptionKey[0], encryptionKey.size())
	{
		if (macKey.size() < hash.outputLen()) throw DsrpException("DatagramEncryptor::DatagramEncryptor: macKey not long enough");
		
	}
	
	void DatagramEncryptor::void decryptAndVerifyMac(const bytes &in, bytes &out, uint64_t &seqNum)
	{	
		out.clear();
			
		const unsigned int lenSize = 2;
		const unsigned int seqSize = 8;
		const unsigned int digestSize = 12;
		
		if (in.size() <= lenSize + seqSize + digestSize) throw DsrpException("Malformed packet decryption attempt");
		
		// First we need to verify the digest
		
		// we compute the correct digest
		
		
		uint16_t dataLen;
		
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
