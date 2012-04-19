#ifndef _ESESSIONMANAGER_H
#define _ESESSIONMANAGER_H

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
#include <map>

#include <udt.h>

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include "bthread.hpp"
#include "edefines.hpp"
#include "esession.hpp"

class ESession;
class ESessionManager;

typedef boost::shared_ptr<sockaddr_storage> Psockaddr_storage;
typedef boost::shared_ptr<ESession> PESession;


/*
Chce si to dat velky pozor na to jak UDT4 inicializuje UDTSOCKET deskriptory, protoze
by se klidne mohlo stat ze by v te mape byla neplatna session a accept by tam pridal
ten stejny identifikator!!!

Navic spravne by ty deskriptory mely byt predeavane pointrama, coz u me nejsou.

*/

class UELHandler
{
	friend class ESessionManager;
	// Zde je dulezite si uvedomit ze nemuzu predavat PESession, protoze by se mi session nikdy neterminovala
	// PESession je zcela interni zalezitost!!!
	virtual void sessionCreated(UDTSOCKET sockcli)=0;
	virtual void sessionDestroyed(UDTSOCKET sockcli)=0;
	virtual void receivedDatagram(UDTSOCKET sockcli, std::string data)=0;

};

class ESessionManager
{
public:
	ESessionManager(boost::asio::io_service& ioService, UELHandler &uelHandler);
	~ESessionManager();
	int startServer(std::string port);
	boost::asio::io_service &getIoService();

private:
	
	friend class ESession; // because of destroySession
	friend void ereceiver(ESessionManager *sesman);
	
	void addSession(PESession ses); // musi byt volano ve strandMap
	void destroySession(UDTSOCKET sockli);  // musi byt volano ve strandMap
	void sendToSession(UDTSOCKET sockli, std::string data);  // musi byt volano ve strandMap
	
	boost::asio::io_service &ios;
	boost::asio::strand strandMap;
	background_worker<boost::asio::io_service> workReceiver;
	UELHandler &uelh;
	
	std::map<UDTSOCKET, PESession> sessions;
	UDTSOCKET serv;
};

//Musi byt copyable a movable kvuli boost::thread
void ereceiver(ESessionManager *sesman);
void ereceiver_finished();

#endif
