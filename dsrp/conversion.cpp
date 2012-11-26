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

#include <algorithm>
#include <iostream>
#include "conversion.hpp"

namespace DragonSRP
{	
	const unsigned char * Conversion::bytes2array(const bytes &in, int *lenout)
	{
		*lenout = in.size();
		return &in[0];
	}
	
	bytes Conversion::array2bytes(const unsigned char *in, int len)
	{
		bytes ret;
		ret.resize(len);
		copy(in, in + len, ret.begin());
		return ret;
	}
	
	// returns without \0
	bytes Conversion::string2bytes(const std::string &str)
	{
		bytes out;
		const char *s = str.c_str();
		out.resize(str.size()); // important, otherwise SIGSEGV
		copy(s, s + str.size(), out.begin());
		return out;
	}
	
	// returns without \0
	bytes Conversion::string2bytes(const char *str)
	{
		bytes out;
		out.resize(strlen(str)); // important, otherwise SIGSEGV
		copy(str, str + strlen(str), out.begin());
		return out;
	}
	
	/*
	bytes Conversion::hexstring2bytes(const char *str) // throws conversion exception
	{
		
	}
	*/
	
	char * Conversion::mygetline(char *line, int size)
	{
	  char *newline;

	  if (fgets(line, size, stdin))
	  {
		newline = strchr(line, '\n'); /* check for trailing '\n' */
		if (newline) *newline = '\0'; /* overwrite the '\n' with a terminating null */
		return line;
	  }
	  return NULL;
	}

	int Conversion::hexnormalize(unsigned char *c)
	{
	  if (*c >= '0' && *c <= '9') *c -= 48;
	  else if (*c >= 'A' && *c <= 'F') *c-= 55;
	  else if (*c >= 'a' && *c <= 'f') *c-= 87;
	  else return -1;
	  return 0; // Success
	}

	// returns without \0, return value must be free()d from memory!
	unsigned char * Conversion::hextobyte(const char *hexstring, int *lenout)
	{
	  unsigned char *result;
	  unsigned char c1, c2;
	 
	  if ((strlen(hexstring) % 2) != 0) throw ConversionException("Hex string must have even number of characters.");
	  
	  *lenout = strlen(hexstring) / 2;
	  result = (unsigned char *) malloc(*lenout);

	  for (int i = 0; i < *lenout; i++)
	  {
		c1 = *(hexstring + i * 2);
		c2 = *(hexstring + i * 2 + 1);

		if (hexnormalize(&c1) || hexnormalize(&c2))
		{ 
		  free(result);
		  throw ConversionException("Invalid character detected - hex string can only consist of 0..9 a..f A..F; Didnt you forgot to trim newline?");
		}

		result[i] = c1 * 16 + c2;
	  }

	  return result;
	}

	/*
	void Conversion::print_hex(unsigned char *array, int len)
	{
	  for (int i = 0; i < len; i++) printf("%.2X", array[i]);
	}
	*/

	bytes Conversion::hexstring2bytes(const char *in)
	{
		int len;
		unsigned char *arr = hextobyte(in, &len);
		bytes ret = array2bytes(arr, len);
		free(arr);
		return ret;
	}
	
	bytes Conversion::hexstring2bytes(const std::string &in)
	{
		return hexstring2bytes(in.c_str());
	}
	
	void Conversion::printBytes(const bytes &in)
	{
		std::vector<unsigned char>::const_iterator from = in.begin();
		std::vector<unsigned char>::const_iterator to = in.end();
		for ( ; from!=to; ++from ) printf("%02X", *from);
	}
	
	bytes Conversion::readBytesHex()
	{
		std::string line;
		std::getline(std::cin, line);
		return hexstring2bytes(line);
	}
	
	bytes Conversion::readBytesHexForce(const std::string &message)
	{
		bytes b;
		
		do 
		{
			std::cout << message << ": ";
			b = readBytesHex();
		} while (b.size() == 0);
		
		return b;
	}
	
	
	void Conversion::append(bytes &ret, const bytes &add)
	{
		ret.reserve(ret.size() + add.size());
		ret.insert(ret.end(), add.begin(), add.end());
	}
	
	void Conversion::prepend(bytes &ret, const bytes &add)
	{
		ret.reserve(ret.size() + add.size());
		ret.insert(ret.begin(), add.begin(), add.end());
	}
	
}
