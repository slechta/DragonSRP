

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dsrp/srpclient.hpp"
#include "dsrp/srpclientauthenticator.hpp"
#include "dsrp/user.hpp"
#include "dsrp/ng.hpp"

#include "dsrp/dsrpexception.hpp"
#include "dsrp/conversionexception.hpp"
#include "dsrp/usernotfoundexception.hpp"
#include "dsrp/conversion.hpp"

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
		Ng ng = Ng::predefined(1024);
		OsslMathImpl math(hash, ng);
		
		SrpClient srpclient(math, random, false);
		
		// ask user for credentials
		string strUsername;
		cout << "username: ";
		cin >> strUsername;
		cin.ignore();
		
		string strPassword;
		cout << "password: ";
		cin >> strPassword;
		cin.ignore();
		
		bytes username = Conversion::string2bytes(strUsername);
		bytes password = Conversion::string2bytes(strPassword);
		
		SrpClientAuthenticator sca = srpclient.getAuthenticator(username, password);
		
		// send username and A to server
		bytes A = sca.getA();
		cout << "A (send to server): ";
		Conversion::printBytes(A);
		cout << endl;
		
		// receive salt and B from server
		bytes salt = Conversion::readBytesHexForce("salt(from server)");
		bytes B = Conversion::readBytesHexForce("B(from server)");
		
		// send M1 to server
		bytes M1 = srpclient.getM1(salt, B, sca);
		cout << "M1(send to server): ";
		Conversion::printBytes(M1);
		cout << endl;
		
		// receive M2 from server (or nothing if auth on server side not successful!)
		bytes M2 = Conversion::readBytesHexForce("M2(from server)");
		// if M2 matches we get K
		bytes K = sca.getSessionKey(M2); // this throws exception on bad password
		
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

