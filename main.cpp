

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
	
	/*
	MemoryLookup ml;
	OsslSha256 hash;
	OsslMathImpl<OsslSha256> math;
	OsslRandom rand;
	*/
	
	Ng ng = Ng::predefined(4096);
	
	SrpServer<MemoryLookup, OsslSha256, OsslMathImpl<OsslSha256>, OsslRandom > srpserver(ng);
		
	printf("baf\n");
	 
	return 0;
}
