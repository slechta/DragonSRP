

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dsrp/srpserver.hpp"
#include "dsrp/srpverificator.hpp"
#include "dsrp/srpclient.hpp"
#include "dsrp/user.hpp"
#include "dsrp/ng.hpp"

#include "dsrp/dsrpexception.hpp"
#include "dsrp/conversionexception.hpp"
#include "dsrp/usernotfoundexception.hpp"
#include "dsrp/conversion.hpp"

#include "dsrp/memorylookup.hpp"

#include "ossl/osslsha1.hpp"
#include "ossl/osslmathimpl.hpp"
#include "ossl/osslrandom.hpp"

using namespace DragonSRP;
using namespace DragonSRP::Ossl;
using namespace std;

int main(int argc, char **argv)
{	
	try {
		std::string strUsername;
		cout << "username: ";
		cin >> strUsername;

		bytes username = Conversion::string2bytes(strUsername);
		bytes verificator = Conversion::readBytesHexForce("verificator");
		bytes salt = Conversion::readBytesHexForce("salt");
		bytes A = Conversion::readBytesHexForce("A(from client)");

		User u(username, verificator, salt);
		
		Ng ng = Ng::predefined(1024);
		
		OsslSha1 hash;
		OsslMathImpl math(hash, ng);
		OsslRandom random;
		MemoryLookup lookup;
		
		if (!lookup.userAdd(u))
		{
			cout << "Error: user already exists" << endl;
		}
		
		SrpServer srpserver(lookup, math, random);
		
		printf("baf4B\n");
		SrpVerificator ver = srpserver.getVerificator(username, A);
		
		printf("baf4C\n");
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
