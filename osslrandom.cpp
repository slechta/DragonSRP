
#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>
#include "osslrandom.hpp"

namespace Dsrp
{
	OsslRandom::OsslRandom()
	{
		
	}
	
	bool OsslRandom::getRandom(bytes &out, unsigned int len)
	{
		if (len <= 0) return false; // fail
		unsigned char *r = (unsigned char *) malloc(len);
		if (r == NULL) return false;
		int rval = RAND_bytes(r, len);
		
		if (rval != 1)
		{
			free(r);
			return false;
		}
		
		copy(r, r + len, out.begin());
		free(r);
		return true;
	}
	
}


int init_random()
{    
    FILE *fp = 0;
    unsigned char buff[128];

    fp = fopen("/dev/urandom", "r");
        
    if (fp)
    {
        fread(buff, sizeof(buff), 1, fp);
		fclose(fp);
    }
    else return -1;
	
    RAND_seed(buff, sizeof(buff));
}
