
#include "esession.hpp"
#include "edebug.hpp"

using namespace boost;
using namespace std;

// Constructor
ESession::ESession(ESessionManager *sessionManager, UDTSOCKET socket, Psockaddr_storage addressInfo) : 
	sesman(sessionManager), 
	ios(sessionManager->getIoService()), 
	sock(socket), 
	address(addressInfo),
	tmrKill(sessionManager->getIoService(), boost::posix_time::seconds(5)),
	sessionStrand(sessionManager->getIoService()),
	state(CONSTRUCTED)
{

}

// Destructor
// Destructor is called when shared_ptr references=0
ESession::~ESession()
{
	UDT::close(sock);
	safePrint("SESSION DEALLOCATED");
}

int ESession::setSessionKey(const std::string &skey)
{
	return 0;
}

// Musi byt volano v sessionStrand
void ESession::terminate(PESession ses)
{
	safePrint("state = TERMINATED");
	state = TERMINATED;
}

UDTSOCKET ESession::getSocket()
{
	return sock;
}

ESessionManager *ESession::getManager()
{
	return sesman;
}

void ESession::parseData(PESession ses, std::string data)
{
	if (state == CONSTRUCTED)
	{
		safePrint("ESession::parseData: Error parsing data in CONSTRUCTED state");
		return;
	}
	if (state == TERMINATED) return;

	// Parse here a invoke more async handlers in session strand
	//safePrint("data parser");
}

void ESession::start(PESession ses)
{
	if (state != CONSTRUCTED)
	{
		safePrint("Error: ESession::start() invalid state, terminating ...");
		state = TERMINATED;
		return;
	}

	safePrint("ESession::start(): OK STARTED");
	state = NEGOTIATION;
	// set TmrKill in sessionStrand
	//tmrKill.async_wait(sessionStrand.wrap(boost::bind(&ESession::killMe, ses, ses)));

}

void ESession::killMe(PESession ses)
{
	ios.dispatch(sesman->strandMap.wrap(boost::bind(&ESessionManager::destroySession, sesman, sock)));
}
