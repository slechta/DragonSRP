/* ===============================================================  @
*  DragonSRP, C++ library implementing Secure Remote Protocol       *
*  Copyright (C) 2011 Pavel Slechta                                 *
*  <slechta@email.cz>                                               *
*                                                                   *
*  DragonSRP is free software; you can redistribute it and/or       *
*  modify it under the terms of the GNU Lesser General Public       *
*  License as published by the Free Software Foundation; either     *
*  version 3 of the License, or (at your option) any later version. *
*                                                                   *
*  DragonSRP is distributed in the hope that it will be useful,     *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU *
*  Lesser General Public License for more details.                  *
*                                                                   *
*  You should have received a copy of the GNU Lesser General Public *
*  License along with DragonSRP.                                    *
*  If not, see <http://www.gnu.org/licenses/>.                      *
@  =============================================================== */

/* ===============================================================  @
*  In addition, as a special exception, the copyright holders give  *
*  permission to link the code of portions of this program with the *
*  OpenSSL library under certain conditions as described in each    *
*  individual source file, and distribute linked combinations       *
*  including the two.                                               *
*  You must obey the GNU Lesser General Public License in all       *
*  respects for all of the code used other than OpenSSL.            *
*  If you modify file(s) with this exception, you may extend        *
*  this exception to your version of the file(s), but you are not   *
*  obligated to do so.  If you do not wish to do so, delete this    *
*  exception statement from your version. If you delete this        *
*  exception statement from all source files in the program, then   *
*  also delete it here.                                             *
@  =============================================================== */

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
		
			static const unsigned char *bytes2array(const bytes &in, int *lenout);
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
