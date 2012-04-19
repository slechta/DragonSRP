

#include <stdio.h>
#include "edebug.hpp"

boost::mutex mutPrint;

void safePrint(std::string str)
{
	boost::mutex::scoped_lock lock(mutPrint);
	std::cout << str << std::endl;
}
