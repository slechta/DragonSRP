
#include <openssl/rand.h>
#include "osslrandom.hpp"

namespace Dsrp
{
	OsslRandom::OsslRandom()
	{
		
	}
	
	bytes OsslRandom::getRandom(unsigned int len)
	{
		
	}
	
}


static void init_random()
{    
    FILE *fp = 0;
    unsigned char buff[32];

    fp = fopen("/dev/urandom", "r");
        
    if (fp)
    {
        fread(buff, sizeof(buff), 1, fp);
		fclose(fp);
    }
    else return -1;
	
    RAND_seed(buff, sizeof(buff));
}
