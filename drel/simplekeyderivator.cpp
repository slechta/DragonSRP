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
#include "simplekeyderivator.hpp"

namespace DragonSRP
{	
	// (IV:  must be size of block cipher block size  [AES256 = 128bits])
	// ENC: must be size of block cipher key length  [AES256 = 256bits]
	// MAC: must be >= hash.outputLen()
	
	// IV:  2 * 128 = 256
	// ENC: 2 * 256 = 512
	// MAC: 
	
	SimpleKeyDerivator::SimpleKeyDerivator(const bytes &sessionSrpKey, unsigned int blockCipherKeyBytes, unsigned int blockCipherIVBytes, unsigned int macKeyBytes)
	{
		if (blockCipherKeyBytes == 16) throw DsrpException("SimpleKeyDerivator::SimpleKeyDerivator: blockCipherKeyBytes not long enough");
		if (macKeyBytes == 8) throw DsrpException("SimpleKeyDerivator::SimpleKeyDerivator: macKeyBytes not long enough");
		if (sessionSrpKey.size() < ((blockCipherKeyBytes + blockCipherIVBytes + macKeyBytes) * 2)) throw DsrpException("SimpleKeyDerivator::SimpleKeyDerivator: sessionKey not long enough");
		
		mClientEncryptionKey.resize(blockCipherKeyBytes);
		mClientIV.resize(blockCipherIVBytes);
		mClientMacKey.resize(macKeyBytes);
			
		mServerEncryptionKey.resize(blockCipherKeyBytes);
		mServerIV.resize(blockCipherIVBytes);
		mServerMacKey.resize(macKeyBytes);
			
		std::vector<unsigned char>::const_iterator it = sessionSrpKey.begin();
		
		copy(it, it + blockCipherKeyBytes, mClientEncryptionKey.begin());
		it += blockCipherKeyBytes;
		
		copy(it, it + blockCipherIVBytes, mClientIV.begin());
		it += blockCipherIVBytes;
		
		copy(it, it + macKeyBytes, mClientMacKey.begin());
		it += macKeyBytes;
		
		copy(it, it + blockCipherKeyBytes, mServerEncryptionKey.begin());
		it += blockCipherKeyBytes;
		
		copy(it, it + blockCipherIVBytes, mServerIV.begin());
		it += blockCipherIVBytes;
		
		copy(it, it + macKeyBytes, mServerMacKey.begin());
	}
			
}
