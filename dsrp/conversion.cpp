
#include <algorithm>
#include <iostream>
#include "conversion.hpp"

namespace DragonSRP
{	
	// return value must be deallocated with free!
	unsigned char * Conversion::bytes2array(const bytes &in, int *lenout)
	{
		unsigned char *arr = (unsigned char*) malloc(sizeof(unsigned char) * in.size());
		// should check if bytesIn==NULL !!!!!
		copy(in.begin(), in.end(), arr);
		*lenout = in.size();
		return arr;
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
		getline(std::cin, line);
		return hexstring2bytes(line);
	}
	
	bytes Conversion::readBytesHexForce(const std::string &message)
	{
		bytes b;
		do
		{
			std::cout << message << ": ";
			b = readBytesHex();
		}
		while (b.size() == 0);
		
		return b;
	}
}
