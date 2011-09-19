

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

#include "osslmathimpl.cpp"


using namespace Dsrp;
using namespace std;

int main(int argc, char **argv)
{
	
	
	MemoryLookup ml;
	OsslSha256 hash;
	OsslMathImpl<OsslSha256> math;
	OsslRandom rand;
	
	// SrpServer<MemoryLookup, OsslSha256, OsslMathImpl<OsslSha256>, OsslRandom > srpserver;
	//SrpServer<MemoryLookup, OsslSha256, OsslRandom > srpserver;
		
	printf("baf\n");
	 
	return 0;
}
