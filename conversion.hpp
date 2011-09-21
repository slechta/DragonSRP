
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
		
	};
}

#endif
