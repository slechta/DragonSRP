

#include <stdio.h>
#include <stdlib.h>
#include <string>


#include "srpserver.hpp"
#include "srpclient.hpp"
#include "user.hpp"
#include "userlookup.hpp"
#include "osslsha256.hpp"
#include "osslmathimpl.hpp"


int main(int argc, char **argv)
{
	Dsrp::SrpServer<Dsrp::OsslSha256, Dsrp::OsslMathImpl<Dsrp::OsslSha256> > srpserver;
		
	printf("baf\n");
	
	return 0;
}
