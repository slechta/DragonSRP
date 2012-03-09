#include <string>
#include <iostream>
#include <vector>

#include "hmac.hpp"
#include "../dsrp/conversion.hpp"
#include "macexception.hpp"

/***********************************************************************
 * RFC 2014 Page 3
   Keys need to be chosen at random (or using a cryptographically strong
   pseudo-random generator seeded with a random seed), and periodically
   refreshed.  (Current attacks do not indicate a specific recommended
   frequency for key changes as these attacks are practically
   infeasible.  However, periodic key refreshment is a fundamental
   security practice that helps against potential weaknesses of the
   function and keys, and limits the damage of an exposed key.)
 * *********************************************************************/

namespace DragonSRP
{
	Hmac::Hmac(HashInterface &hashInterface, const bytes &key): hash(hashInterface), mKey(key)
	{
		unsigned int padSize = hash.blockSize();
		
		if (mKey.size() == 0) throw MacException("Mac - empty key provided.");
		//if (mKey.size() < hash.outputLen()) throw MacException("Mac - short key provided.");
		if (mKey.size() > padSize) throw MacException("Mac - too long key provided. Hash it first.");
		
		mKey.reserve(padSize);
		// expand key to match hash block size with zeros
		mKey.resize(padSize, 0x00);
		
		ikeypad.reserve(padSize);
		okeypad.reserve(padSize);

		for (unsigned int i = 0; i < padSize; i++)
		{
			ikeypad.push_back(mKey[i] ^ 0x36);
			okeypad.push_back(mKey[i] ^ 0x5c);
		}
	}
	
	void Hmac::hmac(const bytes &in, bytes &out)
	{
		bytes toHash;
		toHash.reserve(ikeypad.size() + in.size());
		Conversion::append(toHash, ikeypad);
		Conversion::append(toHash, in);
		bytes res = hash.hash(toHash);
		
		toHash.clear();
		toHash.reserve(okeypad.size() + res.size());
		Conversion::append(toHash, okeypad);
		Conversion::append(toHash, res);
		out = hash.hash(toHash);
	}
}
