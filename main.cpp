

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "srpserver.hpp"
#include "srpverificator.hpp"
#include "srpclient.hpp"
#include "user.hpp"

#include "osslsha256.hpp"
#include "osslmathimpl.hpp"
#include "osslrandom.hpp"
#include "conversion.hpp"
#include "memorylookup.hpp"
#include "ng.hpp"

#include "usernotfoundexception.hpp"

using namespace DragonSRP;
using namespace std;

int main(int argc, char **argv)
{	
	try {
		Ng ng = Ng::predefined(4096);
		OsslSha256 hash;
		OsslMathImpl math(hash, ng);
		OsslRandom random;
		MemoryLookup lookup;
		
		// User u(string2bytes("testuser"), )
		// lookup.addUser()
		
		SrpServer srpserver(lookup, math, random);
		SrpVerificator ver = srpserver.getVerificator(Conversion::string2bytes("testuser"), Conversion::string2bytes("libovolne, nutno dodelat hex"));
	}
	catch (UserNotFoundException e)
	{
		cout << "UserNotFoundException: " << e.what() << endl;
	}
	catch (DsrpException e)
	{
		cout << "DsrpException: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "unknown exception occures" << endl;
	}
	
	printf("baf5\n");
	 
	return 0;
}
