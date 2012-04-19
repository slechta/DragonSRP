#ifndef _ESESSION_H
#define _ESESSION_H

#ifndef WIN32
   #include <unistd.h>
   #include <cstdlib>
   #include <cstring>
   #include <netdb.h>
#else
   #include <winsock2.h>
   #include <ws2tcpip.h>
   #include <wspiapi.h>
#endif

#include <iostream>
#include <sstream>
#include <string>

#include <udt.h>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "edefines.hpp"
#include "esessionmanager.hpp"

// Trochu to prehanim, asi by melo jit jen do .cpp
using namespace std;
using namespace boost;

enum SessionState { CONSTRUCTED, NEGOTIATION, AWAITING_FRAME, TERMINATED };


class ESession;
class ESessionManager;

typedef boost::shared_ptr<sockaddr_storage> Psockaddr_storage;
typedef boost::shared_ptr<ESession> PESession;



// Na co davat pozor:
// A) Kazdy complettion handler sessiony musi mit jako parametr PSession ses neboli shared_ptr na sessionu sama kvuli predcasne dealokaci
//	  vyhozeni z mapy u ESessionManagera to plati pro jakykoliv handler, cili i pro deadline_timer completition handler
// B) Na zacatku kazdeho handleru MUSI byt if(state == TERMINATED) return;
//    ... a kdyz kazdeho tak samozrejme i u timeru
//		... je to proto, aby se session normalne ukoncila musi 
//			(... ta se ukonci az skonci vsechny jeji handlery, proto je tam to terminate)
// C) Trida ESession/PSession se tyka jenom UEL vrstcvy, pro vyssi vrstvu musi zustat NEDOTKNUTELNA
//	  ... je to prave kvuli tem shared_ptr, protoze kdyz bych ji predal jako parametr, tak by se jiz nikdy nedealokovala
// D) Vsechny handlery pro danou session MUSI byt volany v sessionStrand (a to i handlery v handlerech)!
// E) Pokud ESession chce sama zabit kvuli timeoutu ucini tak volanim killMe() nikoliv terminate()!

class ESession
{
public:
	//Constructor
	ESession(ESessionManager *sessionManager, UDTSOCKET socket, Psockaddr_storage adressInfo);
	
	//Destructor
	~ESession();
	
	//Getters
	ESessionManager *getManager();
	UDTSOCKET getSocket();
	
	//Setters
	int setSessionKey(const std::string &skey);
	
	// Nutno si uvedomit, ze je nutno zajistit aby ESession existovala kvuli pipeam apod.
	// Botan::MemoryVector<Botan::byte> ESession::dataToFrame(const Botan::MemoryRegion<Botan::byte> &data, E_SEQTYPE seqnum);
	

private:
	 friend class ESessionManager;


 // HANDLERS:
	 void start(PESession ses);  //sessionStrand // call only once! 

	 // set termination status
	 // can call only ESessionManager, use killMe() instead
	 void terminate(PESession ses); // sessionStrand
	 void killMe(PESession ses);
	 void parseData(PESession ses, std::string data); //sessionStrand

	 ESessionManager *sesman; // Trochu nebezpecny, ale nemelo by vadit
	 boost::asio::io_service &ios;
	 UDTSOCKET sock;
     Psockaddr_storage address;
	 boost::asio::deadline_timer tmrKill;
	 boost::asio::strand sessionStrand; // bacha na dealokaci, ale chova se lip jak timer
     SessionState state; // Pozor na soubeh

	 E_SEQTYPE expectedRX;
	 E_SEQTYPE nextTX;
};

#endif
