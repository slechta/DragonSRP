

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

#define SALTLEN 32

using namespace DragonSRP;
using namespace DragonSRP::Ossl;
using namespace std;

int main(int argc, char **argv)
{	
	try {
		OsslSha1 hash;
		OsslRandom random;
		Ng ng = Ng::predefined(1024);
		cout << "INFO: using RFC5054 Appendix A 1024 bit N,g pair" << endl;
		OsslMathImpl math(hash, ng);
		
		SrpClient srpclient(math, random, false);
		
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
		
		bytes salt;
		if (salt.size() == 0) salt = random.getRandom(SALTLEN);
		
		bytes verificator = math.calculateVerificator(username, password, salt);
		
		cout << endl << "*** RESULT ***" << endl;
		cout << "username: " << strUsername << endl;
		cout << "salt: ";
		Conversion::printBytes(salt);
		cout << endl << "verificator: ";
		Conversion::printBytes(verificator);
		cout << endl;
	
        cout << "ok - you can now use these parameters in server_test program" << endl;
		return 0;			
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


