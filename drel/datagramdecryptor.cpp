
#include <string.h>
#include <stdio.h>

#include "datagramdecryptor.hpp"

namespace DragonSRP
{

	DatagramDecryptor::DatagramDecryptor(const bytes &encryptionKey, const bytes &IV, const bytes &macKey) :
		aesCtr(&IV[0], IV.size(), &encryptionKey[0], encryptionKey.size()),
		hmac(sha1, macKey)
	{
		if (macKey.size() < sha1.outputLen()) throw DsrpException("DatagramEncryptor::DatagramEncryptor: macKey not long enough");
		
	}
	
	unsigned int DatagramDecryptor::getOverheadLen()
	{
		return DSRP_ENCPARAM_TOTALOVERHEAD;
	}
	
	// Assumes that sizeof(data) >= inLen - getOverheadLen() 
	void DatagramDecryptor::decryptAndVerifyMac(const unsigned char *in, unsigned int inLen, unsigned char *data, unsigned int *dataLen, uint64_t *seqNum)
	{			
		if (inLen <= DSRP_ENCPARAM_TOTALOVERHEAD) throw DsrpException("Malformed packet decryption attempt");
		
		// First we need to verify the digest so we first compute the correct digest an then compare it
		unsigned char correctDigest[hmac.outputLen()];
		hmac.hmac(in, inLen - DSRP_ENCPARAM_TRUNCDIGEST_SIZE, correctDigest);
		
		// Compare
		for (int i = 0; i < DSRP_ENCPARAM_TRUNCDIGEST_SIZE; i++)
		{
			if (correctDigest[i] != in[(inLen - DSRP_ENCPARAM_TRUNCDIGEST_SIZE) + i]) throw DsrpException("Mac signature inccorect. Possible attack detected.");
		}
		
		// Now we check if the data length is correct
		uint16_t realDataLen = inLen - DSRP_ENCPARAM_TOTALOVERHEAD;
		uint16_t signDataLen;
		
		memcpy(&signDataLen, in, DSRP_ENCPARAM_LEN_SIZE); // May cause endianess issues
		
		if (realDataLen != signDataLen) throw DsrpException("Malformed packet data field length. Possible attack detected.");
		*dataLen = signDataLen;
		
		memcpy(seqNum, in + DSRP_ENCPARAM_LEN_SIZE, DSRP_ENCPARAM_SEQ_SIZE); // Extract seqNum
		
		// Finally decrypt data
		// in -----decrypt-----> data
		aesCtr.encrypt(&in[DSRP_ENCPARAM_LEN_SIZE + DSRP_ENCPARAM_SEQ_SIZE], data, realDataLen); // Possible optim. direct to &out[lenSize + seqSize] , // throws on error
	}


}
