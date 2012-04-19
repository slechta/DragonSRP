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
#include <stdio.h>
#include <stdlib.h>

#include <udt.h>

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include "edefines.hpp"
#include "edebug.hpp"
#include "esession.hpp"
#include "esessionmanager.hpp"
#include "udtclient.hpp"

boost::mutex cout_mutex;

void wait(int seconds)
{
    {
        boost::mutex::scoped_lock lock(cout_mutex);
        std::cout << "Wait for " << seconds << " seconds" << std::endl;
    }
    boost::xtime xt;
    boost::xtime_get(&xt, boost::TIME_UTC);
    xt.sec += seconds;
    boost::thread::sleep(xt);
}

void wait_finished()
{
    {
        boost::mutex::scoped_lock lock(cout_mutex);
        std::cout << "Waiting finished." << std::endl;
    }
}

class Uha : public UELHandler
{
	void sessionCreated(UDTSOCKET sockcli)
	{
		safePrint("UEL: Session created");
	}
	
	void sessionDestroyed(UDTSOCKET sockcli)
	{
		safePrint("UEL: Session destroyed");
	}
	
	void receivedDatagram(UDTSOCKET sockcli, std::string data)
	{
		safePrint("UEL: Received datagram");
	}
};

void printxx(boost::shared_ptr<boost::asio::deadline_timer> tmr)
{
	safePrint("works");
}

int main (int argc, char *argv[])
{
  boost::asio::io_service ios;

  boost::thread_group threads;
  std::size_t thread_count = 5;
/*  
  {
	  boost::shared_ptr<boost::asio::deadline_timer> tmr(new boost::asio::deadline_timer(ios, boost::posix_time::seconds(5)));
	  tmr->async_wait(boost::bind(printxx, tmr));
  }
  ios.run();
 */
  
	  
/*
  background_worker<boost::asio::io_service> bg_thread(ios);
  bg_thread.async_run(boost::bind(wait, 1), wait_finished);
  bg_thread.async_run(boost::bind(wait, 1), wait_finished);
  ios.run();

  bg_thread.async_run(boost::bind(wait, 1), wait_finished);
  ios.reset();
  ios.run();

  safePrint("exited ios");
*/
if (argc == 1)
{
	boost::asio::io_service::work work(ios);

	Uha u;
	ESessionManager man(ios, u);
	int x = man.startServer("9000");
	printf("startServer return value: %d\n", x);

	
	for (std::size_t i = 0; i < thread_count; ++i)
    threads.create_thread(boost::bind(&asio::io_service::run, &ios));


    //ios.stop();
    threads.join_all();
	//ios.run();

	safePrint("exited ios");
	UDT::cleanup();
	
}

  if (argc == 3)
  {
	 safePrint("argc is 2");
/*
	  if (!strcmp(argv[1], "s"))
	  {
	      safePrint("starting server");
		  start_server();
	  }
*/
	  if (!strcmp(argv[1], "c"))
	  {
		safePrint("client");
		start_client(argv[2]);
	  }
  }

  getchar();
  return 0;
 
}
