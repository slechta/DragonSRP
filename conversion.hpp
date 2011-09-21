
#ifndef DSRP_CONVERSION_HPP
#define DSRP_CONVERSION_HPP

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include "common.hpp"
#include "conversionexception.hpp"

namespace DragonSRP
{
	class Conversion
	{
		public:
			static unsigned char *bytes2array(const bytes &in, int *lenout); // must free()
			static bytes array2bytes(const unsigned char *in, int len);
			
			static bytes string2bytes(const std::string &str);
			static bytes string2bytes(const char *str);
				
		// some should be private
			static char *mygetline(char *line, int size);
			
			static unsigned char *hextobyte(const char *hexstring, int *lenout);
			static unsigned char *hexscan(int maxbyteslen, int *resultlen);
			static void print_hex(unsigned char *array, int len);			
			
		private:
			static int hexnormalize(unsigned char *c); // should rather throw an exception - not really, deallocation
	};
}

#endif
