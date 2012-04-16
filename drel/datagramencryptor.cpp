
#include <string.h>

#include <stdio.h>

#include "datagramencryptor.hpp"

// check if key persist aes_encrypt_key; !!!

namespace DragonSRP
{

	DatagramEncryptor::DatagramEncryptor(const bytes &encryptionKey, const bytes &IV, const bytes &macKey) :
		aesCtr(&IV[0], IV.size(), &encryptionKey[0], encryptionKey.size()),
		hmac(sha1, macKey)
	{
		if (macKey.size() < sha1.outputLen()) throw DsrpException("DatagramEncryptor::DatagramEncryptor: macKey not long enough");
		
	}
	
	unsigned int DatagramEncryptor::getOverheadLen()
	{
		return DSRP_ENCPARAM_TOTALOVERHEAD;
	}
	
	// Assumes sizeof(out) >= plaintextLen + getOverheadLen()   [MTU + OVERHEAD]
	void DatagramEncryptor::encryptAndAuthenticate(const unsigned char *plaintext, unsigned int plaintextLen, unsigned char *out, unsigned int *outLen) // throws
	{
		uint16_t dataLen = plaintextLen; //  possible endianess inssues
		uint64_t seqNum = aesCtr.getCurrentIV() + 1;
		
		memcpy(out, &dataLen, DSRP_ENCPARAM_LEN_SIZE); // set LEN
		memcpy(out + DSRP_ENCPARAM_LEN_SIZE, &seqNum, DSRP_ENCPARAM_SEQ_SIZE); // set SEQ
		
		// SET ENC(DATA)
		// in -----encrypt-----> encdata
		// ---> seqNum
		printf("starting aesCtr.encrypt()\n");
		aesCtr.encrypt(plaintext, out + DSRP_ENCPARAM_LEN_SIZE + DSRP_ENCPARAM_SEQ_SIZE , plaintextLen); // Possible optim. direct to &out[lenSize + seqSize]
		printf("finished aesCtr.encrypt()\n");
		
		// SET DIGEST
		// Add trunc digest
		unsigned char digest[hmac.outputLen()];
		hmac.hmac(out, DSRP_ENCPARAM_LEN_SIZE + DSRP_ENCPARAM_SEQ_SIZE + plaintextLen, digest);
		memcpy(out + DSRP_ENCPARAM_LEN_SIZE + DSRP_ENCPARAM_SEQ_SIZE + plaintextLen, digest, DSRP_ENCPARAM_TRUNCDIGEST_SIZE); // could be avoided (optim.)
		
		*outLen = plaintextLen + DSRP_ENCPARAM_LEN_SIZE + DSRP_ENCPARAM_SEQ_SIZE + DSRP_ENCPARAM_TRUNCDIGEST_SIZE;
		printf("plaintextLen: %d\n", plaintextLen);
		printf("outLen: %d\n", *outLen);
	}


}
