

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dsrp/dsrpexception.hpp"
#include "dsrp/conversionexception.hpp"
#include "dsrp/conversion.hpp"

#include "ossl/osslmd5.hpp"

#include "mac/hmac.hpp"
#include "mac/macexception.hpp"

#include "ossl/osslsha1.hpp"
#include "ossl/osslmathimpl.hpp"
#include "ossl/osslrandom.hpp"

using namespace DragonSRP;
using namespace DragonSRP::Ossl;
using namespace std;

const std::string rfc_1x_key("0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b");
const std::string rfc_1_data("Hi There");
const std::string rfc_1x_digest("9294727a3638bb1c13f48ef8158bfc9d");

const std::string rfc_2_key("Jefe");
const std::string rfc_2_data("what do ya want for nothing?");
const std::string rfc_2x_digest("750c783e6ab0b503eaa86e310a5db738");

const std::string rfc_3x_key("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
const std::string rfc_3x_data("DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD");
const std::string rfc_3x_digest("56be34521d144c88dbb8c733f0e8b3f6");


int main(int argc, char **argv)
{	
	try {
		OsslMd5 hash;
		Hmac hmac1(hash, Conversion::hexstring2bytes(rfc_1x_key));
		Hmac hmac2(hash, Conversion::string2bytes(rfc_2_key));
		Hmac hmac3(hash, Conversion::hexstring2bytes(rfc_3x_key));
		
		bytes cdigest1, cdigest2, cdigest3;
		
		hmac1.hmac(Conversion::string2bytes(rfc_1_data), cdigest1);
		hmac2.hmac(Conversion::string2bytes(rfc_2_data), cdigest2);
		hmac3.hmac(Conversion::hexstring2bytes(rfc_3x_data), cdigest3);
		
		bytes rdigest1 = Conversion::hexstring2bytes(rfc_1x_digest);
		bytes rdigest2 = Conversion::hexstring2bytes(rfc_2x_digest);
		bytes rdigest3 = Conversion::hexstring2bytes(rfc_3x_digest);
		
		cout << "calc digest1: ";
		Conversion::printBytes(cdigest1);
		cout << endl;
		
		cout << "real digest1: ";
		Conversion::printBytes(rdigest1);
		cout << endl;
		
		if (cdigest1 != rdigest1)
		{
			cout << "digest one does not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		
		cout << "calc digest2: ";
		Conversion::printBytes(cdigest2);
		cout << endl;
		
		cout << "real digest2: ";
		Conversion::printBytes(rdigest2);
		cout << endl;
		
		if (cdigest2 != rdigest2)
		{
			cout << "digest two does not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		
		cout << "calc digest3: ";
		Conversion::printBytes(cdigest3);
		cout << endl;
		
		cout << "real digest3: ";
		Conversion::printBytes(rdigest3);
		cout << endl;
		
		if (cdigest3 != rdigest3)
		{
			cout << "digest three does not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		
		cout << "Vectors match. Test SUCCESSFUL." << endl;
		
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

