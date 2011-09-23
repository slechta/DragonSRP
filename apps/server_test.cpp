

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dsrp/srpserver.hpp"
#include "dsrp/srpverificator.hpp"
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
		OsslSha1 hash;
		OsslRandom random;
		MemoryLookup lookup;
		Ng ng = Ng::predefined(1024);
		OsslMathImpl math(hash, ng);
		
		SrpServer srpserver(lookup, math, random);
		
		// Create user
		std::string strUsername;
		cout << "username: ";
		cin >> strUsername;

		bytes username = Conversion::string2bytes(strUsername);
		bytes verificator = Conversion::readBytesHexForce("verificator");
		bytes salt = Conversion::readBytesHexForce("salt");
		
		User u(username, verificator, salt);
		
		if (!lookup.userAdd(u))
		{
			cout << "Error: user already exists" << endl;
		}
		// End of user creation
		
		
		
		// Receive username and A from client
		
		/*
		std::string strUname;
		cout << "username(from client): ";
		cin >> strUname;
		bytes uname = Conversion::string2bytes(strUname);
		*/
		
		bytes A = Conversion::readBytesHexForce("A(from client)");
		
		SrpVerificator ver = srpserver.getVerificator(username, A);
		
		// Send salt, B to client
		//printBytes(ver.getSalt());
		//printBytes(ver.getB());
		
		// receive M1 from client
		bytes M1_fc = Conversion::readBytesHexForce("M1(from client)");
		
		bytes M2_to_client;
		bytes K; // secret session key
		// if M1 is OK we get M2 and K otherwise exception is thrown
		ver.authenticate(M1_fc, M2_to_client, K);
		
		//send M2 to client
		//printBytes(M2_to_client);
		
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
		cout << "unknown exception occured" << endl;
	}

	printf("end\n");
	return 0;
}

