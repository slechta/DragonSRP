

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "srpserver.hpp"
#include "srpclient.hpp"
#include "user.hpp"

#include "osslsha256.hpp"
#include "osslmathimpl.hpp"
#include "osslrandom.hpp"
#include "osslhelp.hpp"
#include "memorylookup.hpp"
#include "ng.hpp"

using namespace Dsrp;
using namespace std;

int main(int argc, char **argv)
{	
	Ng ng = Ng::predefined(4096);
	OsslSha256 hash;
	OsslMathImpl math(hash, ng);
	OsslRandom random;
	MemoryLookup lookup;
	
	SrpServer srpserver(lookup, math, random);
		
	printf("baf\n");
	 
	return 0;
}
