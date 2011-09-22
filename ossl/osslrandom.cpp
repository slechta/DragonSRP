
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include "osslrandom.hpp"

namespace DragonSRP
{
	OsslRandom::OsslRandom() :
		initOk(false)
	{
		FILE *fp = 0;
		unsigned char buff[128];

		fp = fopen("/dev/urandom", "r");
        
		if (fp)
		{
			fread(buff, sizeof(buff), 1, fp);
			fclose(fp);
		}
		else throw DsrpException("Could not initialize random number generator");
	
		RAND_seed(buff, sizeof(buff));
		initOk = true;
	}
	
	bytes OsslRandom::getRandom(unsigned int lenBytes)
	{
		if (!initOk) throw DsrpException("Could not get random number - PRNG not initialized");
		if (lenBytes <= 0) throw DsrpException("Could not get random number - size is zero or negative");
		unsigned char *r = (unsigned char *) malloc(lenBytes);
		if (r == NULL) throw DsrpException("Could not get random number - malloc() failed");;
		int rval = RAND_bytes(r, lenBytes);
		
		if (rval != 1)
		{
			free(r);
			throw DsrpException("Could not get random number");
		}
		
		bytes out;
		copy(r, r + lenBytes, out.begin());
		free(r);
		return out;
	}
	
}
