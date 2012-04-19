
#include "esessionmanager.hpp"
#include "edebug.hpp"

#define E_DATASIZE 1500

ESessionManager::ESessionManager(boost::asio::io_service& ioService, UELHandler &uelHandler) : 
	ios(ioService), 
	strandMap(boost::asio::strand(ioService)), 
	workReceiver(ioService),
	uelh(uelHandler)
{

}

// Call only once, otherwise serv socket will be lost
int ESessionManager::startServer(std::string port)
{
    // use this function to initialize the UDT library
	// Multiple calls to this function are harmless see udt documenatation
    UDT::startup();

	addrinfo* res;
	addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	if (0 != getaddrinfo(NULL, port.c_str(), &hints, &res)) return E_ERROR_INVALIDPORT;
	serv = UDT::socket(res->ai_family, res->ai_socktype, res->ai_protocol);


	if (UDT::ERROR == UDT::bind(serv, res->ai_addr, res->ai_addrlen))
	{
		safePrint(UDT::getlasterror().getErrorMessage());
		freeaddrinfo(res);
		return E_ERROR_BINDFAILED;
	}

	freeaddrinfo(res);

	if (UDT::ERROR == UDT::listen(serv, E_MAX_PENDING_CONNECTIONS))
	{
		safePrint(UDT::getlasterror().getErrorMessage());
		return E_ERROR_LISTENFAILED;
	}
	
	// A little wonder running in another thread
	workReceiver.async_run(boost::bind(ereceiver, this), ereceiver_finished);
	
	return 0;
}

ESessionManager::~ESessionManager()
{
	UDT::close(serv); // Jen aby to nebylo nebezpecny
}

// This is intentionaly not in ESessionManager class because Boost::Thread needs copyable and movable
// Must be called with same ioService as SessionManager

/*
Zde jsou potencialni 3 race condition:
  1) Destroy <-> Accpet race condition
     scenar 1:
	 a) do exceptfds se dostane broken session
     b) vyvola se asynchronni odstraneni UDTSOCKET z mapy
	 c) bude ale pokracovat ereceiver thread
	 d) v ereceiveru nastane accept se stejnym UDTSOCKET id jako se predtim odstranil
	 e) vyvola se asynchronni operace pridani do mapy
	 f) v te uz existuje

  2) Accept <-> Close race condition
	 a) do exceptfds se dostane broken session
     b) vyvola se asynchronni odstraneni UDTSOCKET z mapy
	 c) bude ale pokracovat ereceiver thread
	 d) v ereceiveru nastane accept se stejnym UDTSOCKET id jako se predtim odstranily
	 e) nyni ESession zavola UDT::close() na svuj "potencionalne nevalidni" UDTSOCKET a tim odstrihne nove spojeni
   --->>> Reseni:
		dokud nedam close(), nemuze duplicit nikdy nastat, proto pred volanim UDT::close()
		v ESession odstrani ESession socket z mapy	musim ale zablokovat veskery send puvodni session

		jenze handler odsranovani z mapy se muze pustit pozdeji nez onen addSession() u acceptu.
		to se resi tim ze se da ios.dispatch() misto ios.post()

		Korektni zavreni ESession v sobe sama:
			state = TERMINATE
			ios.dispatch(strandMap.wrap(removeFromMap));
			close(socket)

  3) Send <-> Recv race condition ->> Ale nemelo by nastat, protoze UDT4 ma pravdepodobne lock na concurrent send <-> recv


  Pozn.: 1 a 2 jen tak nenastane, protoze se nove UDTSOCKET identifikatory od UDT::Startup() dekrementuji od nuly.

*/
void ereceiver(ESessionManager *sesman)
{
	// Pozor, race condition na sesman->serv!!! needs strand (something like critical section)
	safePrint("recevier started");

	UDTSOCKET serv = sesman->serv;
	UDTSOCKET sockcli;
	int addrlen = sizeof(sockaddr_storage);
	std::vector<UDTSOCKET> socks, readfds, writefds, exceptfds;
	socks.push_back(serv); // Accept socket


	char data[E_DATASIZE];
	int rcvsize;

	while(1) //accept is blocking so this is ok
	{
		UDT::selectEx(socks, &readfds, &writefds , &exceptfds, E_SELECTEX_TIMEOUT);
		
		// Pro vsechny read sockety
		BOOST_FOREACH(UDTSOCKET sck, readfds)
		{
			// Mozna, ale jenom mozna by se dalo urychlit za predpokladu ze serversocket bude vzdy na zacatku for_each(.begin() + 1, ...)
			if (sck == serv) 
			{
				// We have got an accept request
				safePrint("gotAccpet");

				Psockaddr_storage clientaddr(new sockaddr_storage);
				
				if (UDT::INVALID_SOCK == (sockcli = UDT::accept(serv, (sockaddr*)clientaddr.get(), &addrlen)))
				{
					 safePrint(UDT::getlasterror().getErrorMessage());
					 // Zde si maximalne zavolame error handler :)
					 //safePrint("acc sock invalid");
					 //return 0;
				}
				
				//Nyni si ho pridame klineta do vectoru
				socks.push_back(sockcli);

				PESession ses(new ESession(sesman, sockcli, clientaddr));

				// Execute addSession() in ios thread in strand
				// This does it immediately
				sesman->ios.dispatch(sesman->strandMap.wrap(boost::bind(&ESessionManager::addSession, sesman, ses)));
			}
			else
			{
				//safePrint("receiving");
				// Nacte cast dat
				// Nikdy nebude blokovat, protoze data jsou jiz diky selectEx() k dispozici
				// Otazka: Co kdyz sck uz nebude platny?? Bude to blokovat nebo hodi jen error?
				rcvsize = UDT::recvmsg(sck, data, E_DATASIZE);
				// Got new data here
				if (rcvsize == UDT::ERROR)
				{
					safePrint(UDT::getlasterror().getErrorMessage());
				}
				
				//safePrint("received");
				// Send data to session
				sesman->ios.dispatch(sesman->strandMap.wrap(boost::bind(&ESessionManager::sendToSession, sesman, sockcli, std::string(data, rcvsize))));

			} // end of if (sck == serv)
		} // end of BOOST_FOREACH(UDTSOCKET sck, readfds)
			
		
		// Broken sessions
		if (!exceptfds.empty())
		{
			safePrint("exceptfds processing ...");
			// Remove all broken sessions from map
			BOOST_FOREACH(UDTSOCKET sck, exceptfds)
			{
				//safePrint("broken session eraser");
				sesman->ios.dispatch(sesman->strandMap.wrap(boost::bind(&ESessionManager::destroySession, sesman, sck)));
			}

			// We do not want broken sessions in our recv vector
			// Remove exceptfds from socks vector
			vector<UDTSOCKET> diff(socks.size());
			sort(socks.begin(), socks.end());
			sort(exceptfds.begin(), exceptfds.end());
			vector<UDTSOCKET>::iterator it = set_difference (socks.begin(), socks.end(), exceptfds.begin(), exceptfds.end(), diff.begin());
			
			// thred unsafe!
			/*
			cout << "difference has " << int(it - diff.begin()) << " elements.\n" << endl;
			cout << "sockssize:" << socks.size() << endl;
			cout << "exceptfdssize:" << exceptfds.size() << endl;
			cout << "diffsize:" << diff.size() << endl;
			*/
			socks.assign(diff.begin(), it);
			
		} // end of if (!exceptfds.empty())

		
	} // end of while(1)
}

void ereceiver_finished()
{
	safePrint("receiver finished");
}

// musi byt volano ve strandMap
void ESessionManager::addSession(PESession ses)
{
	UDTSOCKET sockcli = ses->getSocket();
	std::pair<std::map<UDTSOCKET, PESession>::iterator, bool> ret = sessions.insert(make_pair(sockcli, ses));

	if (!ret.second)
	{
		safePrint("addSession():ERROR: Duplicit UDTSOCKET");
	}

	
	ios.dispatch(ses->sessionStrand.wrap(boost::bind(&ESession::start, ses, ses)));
	//ios.post(boost::bind(&UELHandler::sessionCreated, &uelh, sockcli));
}

// musi byt volano ve strandMap
void ESessionManager::destroySession(UDTSOCKET sockcli)
{
	std::map<UDTSOCKET, PESession>::iterator it = sessions.find(sockcli);
	if (it == sessions.end())
	{
		safePrint("ESessionManager::destroySession: Session not found");
		return;
	}

	// must be dispatch otherwise race condition may occur
	ios.dispatch(it->second->sessionStrand.wrap(boost::bind(&ESession::terminate, it->second, it->second)));

	sessions.erase(it);
	// je to &uelh spravne?
    // ios.post(boost::bind(&UELHandler::sessionDestroyed, &uelh, sockcli));
}

// musi byt volano ve strandMap
void ESessionManager::sendToSession(UDTSOCKET sockli, std::string data)
{
	std::map<UDTSOCKET, PESession>::iterator it = sessions.find(sockli);
	
	if (it == sessions.end())
	{
		// This usually doesnt indicate any problem
		// Can occur when session is calling killMe() to UDT:close() in ESession destructor
		safePrint("ESessionManager::sendToSession: Session not found");
		return;
	}

	ios.dispatch(it->second->sessionStrand.wrap(boost::bind(&ESession::parseData, it->second, it->second, data)));
}

boost::asio::io_service &ESessionManager::getIoService()
{
	return ios;
}
