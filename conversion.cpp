
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

	unsigned char * Conversion::hextobyte(const char *hexstring, int *lenout)
	{
	  unsigned char *result;
	  int i;
	  unsigned char c1, c2;
	 
	  *lenout = 0;
	  if ((strlen(hexstring) % 2) != 0) return NULL;
	  
	  *lenout = strlen(hexstring) / 2;
	  result = (unsigned char *) malloc(*lenout);
	  if (result == NULL) return NULL;

	  for (i = 0; i < *lenout; i++)
	  {
		c1 = *(hexstring + i * 2);

		if (hexnormalize(&c1))
		{ 
		  free(result);
		  return NULL;
		}

		c2 = *(hexstring + i * 2 + 1);

		if (hexnormalize(&c2))
		{ 
		  free(result);
		  return NULL;
		}

		result[i] = c1 * 16 + c2;
	  }

	  return result;
	}

	unsigned char * Conversion::hexscan(int maxbyteslen, int *resultlen)
	{
	   char *line;
	   char *hexstring;
	   unsigned char *result;
	   int linemaxlen;

	   *resultlen = 0;
	   linemaxlen = (maxbyteslen + 1) * 2;

	   line = (char *) malloc(sizeof(char) * linemaxlen);
	   if (line == NULL) return NULL;

	   if (mygetline(line, linemaxlen) == NULL)
	   {
		 free(line);
		 return NULL;
	   }

	   result = hextobyte(line, resultlen);
	   free(line);
	   return result;
	}

	void Conversion::print_hex(unsigned char *array, int len)
	{
	  int i;
	  for (i = 0; i < len; i++) printf("%.2X", array[i]);
	}
}
