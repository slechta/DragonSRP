
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "dsrp/common.hpp"
#include "dsrp/dsrpexception.hpp"
#include "drel/datagramencryptor.hpp"
#include "drel/datagramdecryptor.hpp"
#include "drel/simplekeyderivator.hpp"
#include "drel/aesexception.hpp"

#define MAX_DATA_LEN 1500

using namespace std;
using namespace DragonSRP;

int sessionKey[128]  =   {0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC,
						  0xFE, 0x5B, 0x4A, 0xCC, 0xFE, 0x5B, 0x4A, 0xCC};

unsigned char data[] = "hello";

void printVar(const char *szVarname, const unsigned char *data, unsigned int len)
{
	printf("%s: ", szVarname);
	for (unsigned int i = 0; i < len; i++) printf("%02X", data[i]);
	printf("\n");
}

int main(int argc, char *argv[])
{	
	try {
		bytes bSessionKey;
		
		bSessionKey.assign(sessionKey, sessionKey + 128);
		
		SimpleKeyDerivator skd(bSessionKey, 32, 7, 20);
		
		// printf("macKeySize: %d\n", skd.getClientMacKey().size());
		
		DatagramEncryptor enc(skd.getClientEncryptionKey(), skd.getClientIV(), skd.getClientMacKey());
		DatagramDecryptor dec(skd.getClientEncryptionKey(), skd.getClientIV(), skd.getClientMacKey());
		
		printf("data: %s\n", data);
		
		unsigned int dataLen = sizeof(data);
		printVar("data", data, dataLen);
		
		if (dataLen > MAX_DATA_LEN)
		{
			printf("data too big\n");
			return -1;
		}
			
		unsigned int encpacketLen;
		unsigned char encpacket[enc.getOverheadLen() + MAX_DATA_LEN];

		enc.encryptAndAuthenticate((unsigned char *)data, dataLen, encpacket, &encpacketLen);
		
		printf("encpacketLen: %d\n", encpacketLen);
		printVar("encpacket", encpacket, encpacketLen);
		
		// Decrypt
		unsigned int decpacketLen;
		unsigned char decpacket[dec.getOverheadLen() + MAX_DATA_LEN];
		uint64_t decseqnum;
		
		dec.decryptAndVerifyMac(encpacket, encpacketLen, decpacket, &decpacketLen, &decseqnum);
		
		if (dataLen != decpacketLen)
		{
			printf("enc/dec fail: different data length\n");
			return -1;
		}
		
		for (int i = 0; i < dataLen; i++)
		{
			if (data[i] != decpacket[i])
			{
				printf("enc/dec fail: decrypted data does not match original plaintext data\n");
				return -1;
			}
		}
		
		printf("decrypted text: %s\n", decpacket); // should check term zero;
		printf("finished\n");
	}
	catch (DsrpException &e)
	{
		cout << "DsrpException: " << e.what() << endl;
		return -1;
	}
	catch (AesException &e)
	{
		cout << "AESException: " << e.what() << endl;
		return -1;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "unknown exception occured" << endl;
		return -1;
	}
	
	printf("enc/dec seems ok\n");
}
