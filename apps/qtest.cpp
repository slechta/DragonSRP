
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dsrp/srpclient.hpp"
#include "dsrp/srpclientauthenticator.hpp"
#include "dsrp/srpserver.hpp"
#include "dsrp/srpverificator.hpp"
#include "dsrp/user.hpp"
#include "dsrp/ng.hpp"

#include "dsrp/dsrpexception.hpp"
#include "dsrp/conversionexception.hpp"
#include "dsrp/usernotfoundexception.hpp"
#include "dsrp/conversion.hpp"

#include "dsrp/memorylookup.hpp"

#include "ossl/osslsha512.hpp"
#include "ossl/osslmathimpl.hpp"
#include "ossl/osslrandom.hpp"

using namespace DragonSRP;
using namespace DragonSRP::Ossl;
using namespace std;

#define USERNAME "username"
#define PASSWORD "password"
#define SALTLEN 32
#define PRIMELEN 2048

int main(int argc, char **argv)
{	
	try {
		OsslSha512 hash;
		OsslRandom random;
		MemoryLookup lookup;
		
		Ng ng = Ng::predefined(PRIMELEN);
		OsslMathImpl math(hash, ng);
		
		SrpServer srpserver(lookup, math, random, true);
		SrpClient srpclient(math, random, true);
		
		bytes username = Conversion::string2bytes(USERNAME);
		bytes password = Conversion::string2bytes(PASSWORD);
		
		SrpClientAuthenticator sca = srpclient.getAuthenticator(username, password);
		
		// Create user
		bytes salt;
		salt = random.getRandom(SALTLEN);
		bytes verificator = math.calculateVerificator(username, password, salt);
		
		User u(username, verificator, salt);
		
		if (!lookup.userAdd(u))
		{
			cout << "Error: user already exists" << endl;
			return -1;
		}
		
		SrpVerificator ver = srpserver.getVerificator(username, sca.getA()); // C,A
		bytes M1 = srpclient.getM1(salt, ver.getB(), sca); // s, B		
		bytes M2, K_server;
		ver.authenticate(M1, M2, K_server); // M1	
		bytes K_client = sca.getSessionKey(M2); // M2
		
		if (K_server != K_client)
		{
			cout << "error: client and server K does not match!" << endl;
			return -2;
		}
		
		cout << "success" << endl;
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

