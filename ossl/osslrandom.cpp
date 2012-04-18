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

/* ===============================================================  @
*  This product includes software developed by the OpenSSL Project  *
*  for use in the OpenSSL Toolkit. (http://www.openssl.org/)        *
*                                                                   *
*  This product includes cryptographic software                     *
*  written by Eric Young (eay@cryptsoft.com)                        *
*                                                                   *
*  This product includes software                                   *
*  written by Tim Hudson (tjh@cryptsoft.com)                        *
@  =============================================================== */


#include <stdio.h>
#include <stdlib.h>
#include <openssl/rand.h>

#include "dsrp/conversion.hpp"
#include "osslrandom.hpp"

namespace DragonSRP
{
	OsslRandom::OsslRandom() :
		initOk(false)
	{
		FILE *fp = 0;
		unsigned char buff[128];

		fp = fopen("/dev/urandom", "r");
        
		if (fp)
		{
			size_t count = fread(buff, sizeof(unsigned char), sizeof(buff), fp);
			if (count != sizeof(buff)) throw DsrpException("Could not initialize random number generator - small seed");
			fclose(fp);
		}
		else throw DsrpException("Could not initialize random number generator");
	
		RAND_seed(buff, sizeof(buff));
		initOk = true;
	}
	
	bytes OsslRandom::getRandom(unsigned int lenBytes)
	{
		if (!initOk) throw DsrpException("Could not get random number - PRNG not initialized");
		if (lenBytes <= 0) throw DsrpException("Could not get random number - size is zero or negative");
		unsigned char *r = (unsigned char *) malloc(lenBytes);
		if (r == NULL) throw DsrpException("Could not get random number - malloc() failed");
		int rval = RAND_bytes(r, lenBytes);
		
		if (rval != 1)
		{
			free(r);
			throw DsrpException("Could not get random number");
		}
		
		bytes out = Conversion::array2bytes(r, lenBytes);
		free(r);
		return out;
	}
	
}
