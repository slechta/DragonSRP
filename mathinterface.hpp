
#ifndef DSRP_MATHINTERFACE_HPP
#define DSRP_MATHINTERFACE_HPP

#include "common.hpp"
#include "ng.hpp"
#include "hashinterface.hpp"

namespace Dsrp
{
	class MathInterface
	{
		public:
			MathInterface(HashInterface &hashInterface, Ng ngVal);
            virtual ~MathInterface()=0;
			virtual void calculateA(const bytes &aa, bytes &A_out)=0;
			virtual void clientChallenge(const bytes &salt, const bytes &aa, const bytes &AA, const bytes &BB, const bytes &username, const bytes &password, bytes &K_out, bytes &M1_out)=0;	
			virtual void serverChallange(const bytes &username, const bytes &salt, const bytes &verificator, const bytes &AA, const bytes &bb, bytes &B_out, bytes &M1_out, bytes &M2_out, bytes &K_out)=0;
		protected:
			HashInterface &hash;
			Ng ng;
	};
}

#endif
