/* This small application tests vectors listed
 * in RFC 5054 Appendix B
 * USE THIS APPLICATION ONLY FOR TESTING THE <RFC VECTORS>
 * ANY OTHER USE IS PURE NONSENSE AND VERY INSECURE
 * DUE TO PREDEFINED PRIVATE KEYS
 * WICH IN NORMAL ENVIRONMENT MUST BE ALWAYS RANDOM
 * 
 * Compilation:
 * in order to get this to work, debugging features must be
 * enabled using DSRP_DANGEROUS_TESTING preprocessor definition
 * in the dsrp library itself - needs complete recompilation
 * >> this is a safety feature
 * */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "dsrp/srpserver.hpp"
#include "dsrp/srpclient.hpp"
#include "dsrp/srpverificator.hpp"
#include "dsrp/srpclientauthenticator.hpp"
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

// RFC input values
const std::string rfc_username("alice");
const std::string rfc_password("password123");
const std::string rfc_salt("BEB25379D1A8581EB5A727673A2441EE");
const std::string rfc_a("60975527035CF2AD1989806F0407210BC81EDC04E2762A56AFD529DDDA2D4393"); // this would be normaly random
const std::string rfc_b("E487CB59D31AC550471E81F00F6928E01DDA08E974A004F49E61F5D105284D20"); // this would be normaly random

// RFC output values
const std::string rfc_k("7556AA045AEF2CDD07ABAF0F665C3E818913186F");
const std::string rfc_x("94B7555AABE9127CC58CCF4993DB6CF84D16C124");
const std::string rfc_verificator("7E273DE8696FFC4F4E337D05B4B375BEB0DDE1569E8FA00A9886D8129BADA1F1822223CA1A605B530E379BA4729FDC59F105B4787E5186F5C671085A1447B52A48CF1970B4FB6F8400BBF4CEBFBB168152E08AB5EA53D15C1AFF87B2B9DA6E04E058AD51CC72BFC9033B564E26480D78E955A5E29E7AB245DB2BE315E2099AFB");
const std::string rfc_A("61D5E490F6F1B79547B0704C436F523DD0E560F0C64115BB72557EC44352E8903211C04692272D8B2D1A5358A2CF1B6E0BFCF99F921530EC8E39356179EAE45E42BA92AEACED825171E1E8B9AF6D9C03E1327F44BE087EF06530E69F66615261EEF54073CA11CF5858F0EDFDFE15EFEAB349EF5D76988A3672FAC47B0769447B");
const std::string rfc_B("BD0C61512C692C0CB6D041FA01BB152D4916A1E77AF46AE105393011BAF38964DC46A0670DD125B95A981652236F99D9B681CBF87837EC996C6DA04453728610D0C6DDB58B318885D7D82C7F8DEB75CE7BD4FBAA37089E6F9C6059F388838E7A00030B331EB76840910440B1B27AAEAEEB4012B7D7665238A8E3FB004B117B58");
const std::string rfc_u("CE38B9593487DA98554ED47D70A7AE5F462EF019");
const std::string rfc_S("B0DC82BABCF30674AE450C0287745E7990A3381F63B387AAF271A10D233861E359B48220F7C4693C9AE12B0A6F67809F0876E2D013800D6C41BB59B6D5979B5C00A172B4A2A5903A0BDCAF8A709585EB2AFAFA8F3499B200210DCC1F10EB33943CD67FC88A2F39A4BE5BEC4EC0A3212DC346D7E474B29EDE8A469FFECA686E5A");

int main(int argc, char **argv)
{	
	try {
		MemoryLookup lookup; // does not affect results
		OsslSha1 hash; // SHA1 is used in RFC5054
		
		// This is actually bypassed, but must be set (no effect)
		// Random generator is not used a and b values are set from RFC
		// Note: This is actually very dangerous in production environment
		//       use this FOR TESTING RFC VECTORS ONLY!!!!!!
		OsslRandom random; 
		
		// Load predefined N,g 1024bit RFC values
		Ng ng = Ng::predefined(1024);
		
		OsslMathImpl math(hash, ng);
		
		// test k
		// works only if defined DSRP_DANGEROUS_TESTING
		if (math.k_math != Conversion::hexstring2bytes(rfc_k))
		{
			cout << "k do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: k matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated k= ";
		Conversion::printBytes(math.k_math);
		cout << endl;
		
		SrpServer srpserver(lookup, math, random);
		SrpClient srpclient(math, random);
		
		// Create user
		bytes username = Conversion::string2bytes(rfc_username);
		bytes password = Conversion::string2bytes(rfc_password);
		bytes salt = Conversion::hexstring2bytes(rfc_salt);
		
		// Calculate verificator
		bytes verificator = math.calculateVerificator(username, password, salt);
		
		// test x
		// works only if defined DSRP_DANGEROUS_TESTING
		if (math.x_vgen != Conversion::hexstring2bytes(rfc_x))
		{
			cout << "x do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: x(user generation) matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated x(user generation)= ";
		Conversion::printBytes(math.x_vgen);
		cout << endl;
		
		// Check verificator against rfc
		bytes b_rfc_verificator = Conversion::hexstring2bytes(rfc_verificator);
		if (verificator != b_rfc_verificator)
		{
			cout << "verificators do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: verificator matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated verificator= ";
		Conversion::printBytes(verificator);
		cout << endl;
		
		// Add user to server
		User u(username, verificator, salt);
		if (!lookup.userAdd(u))
		{
			cout << "Error: user already exists" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		
		// ====================================================
		// Here is bypassed random generation of a
		bytes b_rfc_a = Conversion::hexstring2bytes(rfc_a);
		// works only if defined DSRP_DANGEROUS_TESTING
		SrpClientAuthenticator sca = srpclient.getAuthenticator(username, password, b_rfc_a);
		// ====================================================
		
		if (sca.getA() != Conversion::hexstring2bytes(rfc_A))
		{
			cout << "A values do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: A matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated A= ";
		Conversion::printBytes(sca.getA());
		cout << endl;
		
		// ====================================================
		// Here is bypassed random generation of b
		bytes b_rfc_b = Conversion::hexstring2bytes(rfc_b);
		// works only if defined DSRP_DANGEROUS_TESTING
		SrpVerificator ver = srpserver.getVerificator(username, sca.getA(), b_rfc_b);
		// ====================================================
		
		// Now we will verifiy if B matches rfc values
		if (ver.getB() != Conversion::hexstring2bytes(rfc_B))
		{
			cout << "B values do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: B matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated B= ";
		Conversion::printBytes(ver.getB());
		cout << endl;
		
		// receive M1 from client
		bytes M1 = srpclient.getM1(salt, ver.getB(), sca);
		bytes M2;
		bytes server_K; // this is not premaster secret, this is already master secret
		ver.authenticate(M1, M2, server_K); // throws exception on bad password
	
		cout << "INFO: M1= ";
		Conversion::printBytes(M1);
		cout << endl << "INFO: M2= ";
		Conversion::printBytes(M2);
		cout << endl;
		
		bytes client_K = sca.getSessionKey(M2); // throws exception on bad password
		
				
		// test u
		// works only if defined DSRP_DANGEROUS_TESTING
		if (math.u_server != Conversion::hexstring2bytes(rfc_u))
		{
			cout << "u do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: u matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated u= ";
		Conversion::printBytes(math.u_server);
		cout << endl;
		
		// test x
		// works only if defined DSRP_DANGEROUS_TESTING
		if (math.x_client != Conversion::hexstring2bytes(rfc_x))
		{
			cout << "x (clientChallenge) do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: x (client challenge) matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated x(client challenge)= ";
		Conversion::printBytes(math.x_client);
		cout << endl;
		
		// test S (premaster secret) - client
		// works only if defined DSRP_DANGEROUS_TESTING
		if (math.S_client_premaster_secret != Conversion::hexstring2bytes(rfc_S))
		{
			cout << "S client do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: S client matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated S(client)= ";
		Conversion::printBytes(math.S_client_premaster_secret);
		cout << endl;
		
		// test S (premaster secret) - server
		// works only if defined DSRP_DANGEROUS_TESTING
		if (math.S_server_premaster_secret != Conversion::hexstring2bytes(rfc_S))
		{
			cout << "S server do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: S server matches rfc5054 ok" << endl;
		}
		
		cout << "INFO: calculated S(server)= ";
		Conversion::printBytes(math.S_server_premaster_secret);
		cout << endl;
		
		// test K
		if (server_K != client_K)
		{
			cout << "K values do not match" << endl;
			cout << "!!! TEST VECTORS FAILURE !!!" << endl;
			return -1;
		}
		else
		{
			cout << "INFO: master session secret server==client ok" << endl;
		}
		
		// display shared secret
		cout << "INFO: K(master session secret): ";
		Conversion::printBytes(server_K);
		cout << endl;
		
		// if we get here, no exception was thrown
		// if auth fails DsrpException is thrown
		cout << "authentification successful" << endl;
		cout << "ALL TESTS PASSED OK SUCCESS" << endl;
		return 0;
	}
	catch (UserNotFoundException e)
	{
		cout << "UserNotFoundException: " << e.what() << endl;
		cout << "!!! TEST VECTORS FAILURE !!!" << endl;
	}
	catch (DsrpException e)
	{
		cout << "DsrpException: " << e.what() << endl;
		cout << "!!! TEST VECTORS FAILURE !!!" << endl;
	}
	catch (...)
	{
		cout << "unknown exception occured" << endl;
		cout << "!!! TEST VECTORS FAILURE !!!" << endl;
	}

	cout << "end!!! TEST VECTORS FAILURE !!!" << endl;
	return -1;
}
