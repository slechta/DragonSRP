

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
		OsslSha1 hash; // We will use OpenSSL SHA1 implementation
		OsslRandom random; // We will use OpenSSL random number generator
		MemoryLookup lookup; // This stores users in memory (linked-list)
		
		// Load predefined N,g 1024bit RFC values
		Ng ng = Ng::predefined(1024);
		
		OsslMathImpl math(hash, ng);
		SrpServer srpserver(lookup, math, random, false);
		
		// Begin user creation
		std::string strUsername;
		cout << "username: ";
		cin >> strUsername;
		cin.ignore();

		bytes username = Conversion::string2bytes(strUsername);
		bytes verificator = Conversion::readBytesHexForce("verificator");
		bytes salt = Conversion::readBytesHexForce("salt");
		
		User u(username, verificator, salt);
		
		if (!lookup.userAdd(u))
		{
			cout << "Error: user already exists" << endl;
		}
		// End of user creation
		
		
		// Receive A from client
		bytes A = Conversion::readBytesHexForce("A(from client)");
		
		// verifivator is used to authenticate one user(one session)
		SrpVerificator ver = srpserver.getVerificator(username, A);
		
		// Send salt and B to client
		cout << "salt(send to client): ";
		Conversion::printBytes(ver.getSalt());
		cout << endl;
		
		cout << "B(send to client): ";
		Conversion::printBytes(ver.getB());
		cout << endl;
		
		// receive M1 from client
		bytes M1_fc = Conversion::readBytesHexForce("M1(from client)");
		
		bytes M2_to_client;
		bytes K; // secret session key
		
		// if M1 is OK we get M2 and K otherwise exception is thrown
		ver.authenticate(M1_fc, M2_to_client, K);
		
		// send M2 to client
		cout << "M2 (send to client): ";
		Conversion::printBytes(M2_to_client);
		cout << endl;
		
		// display shared secret
		cout << "shared secret session key is: ";
		Conversion::printBytes(K);
		cout << endl;
		
		// if we get here, no exception was thrown
		// if auth fails DsrpException is thrown
		cout << "authentification successful" << endl;
		return 0;
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

	return -1;
}

