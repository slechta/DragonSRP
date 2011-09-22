
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
			// bytes returned from string are always without \0 termination
		
			static unsigned char *bytes2array(const bytes &in, int *lenout); // must free()
			static bytes array2bytes(const unsigned char *in, int len);
			
			static bytes string2bytes(const std::string &str);
			static bytes string2bytes(const char *str);
			
			static bytes hexstring2bytes(const std::string &in);
			static bytes hexstring2bytes(const char *in); // throws ConversionException
			
			static void printBytes(const bytes &in); // prints to stdout in hex
			
			static bytes readBytesHex();
			static bytes readBytesHexForce(const std::string &message);
			
			static void append(bytes &ret, const bytes &add);
			static void prepend(bytes &ret, const bytes &add);
			
			// some should be private
			static char *mygetline(char *line, int size);
						
		private:
			// Rather not use these directly if you dont have to, they are quite dangerous
			static unsigned char *hextobyte(const char *hexstring, int *lenout); // rval must be free()d!!!
			static int hexnormalize(unsigned char *c);
			// static void print_hex(unsigned char *array, int len);
	};
}

#endif
