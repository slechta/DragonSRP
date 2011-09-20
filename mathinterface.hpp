
#ifndef DSRP_MATHINTERFACE_HPP
#define DSRP_MATHINTERFACE_HPP

#include "common.hpp"
#include "ng.hpp"

namespace Dsrp
{
	
	/* This is an iterface to class which just
	 * performs mathematical operations
	 * it doesnt check any constraints.
	 * Checking constraints is done in
	 * SrpServer and SrpClient classes
	 */  
	class MathInterface
	{
		public:
			virtual bytes setNg(Ng ng)=0;
			virtual void calculateA(const bytes &aa, bytes &A_out)=0;
			virtual void clientChallenge(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &K_out, bytes &M1_out)=0;	
			virtual void serverChallange(const bytes &username, const bytes &salt, const bytes &verificator, const bytes &AA, const bytes &bb, bytes &B_out, bytes &M1_out, bytes &M2_out, bytes &K_out)=0;
	};
}

#endif
