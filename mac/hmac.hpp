
#ifndef DSRP_HMAC_HPP
#define DSRP_HMAC_HPP

#include <vector>
#include "../dsrp/hashinterface.hpp"

namespace DragonSRP
{
	class Hmac
	{
		public:
			Hmac(HashInterface &hashInterface, const bytes &key);
			void hmac(const bytes &in, bytes &out);
			
		private: 
			HashInterface &hash;
			bytes mKey;
			bytes ikeypad;
			bytes okeypad;
		
	};

}
#endif
