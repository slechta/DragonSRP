
#ifndef DSRP_SRPSERVER_HPP
#define DSRP_SRPSERVER_HPP

#include "common.hpp"

#include "user.hpp"

#include "lookupinterface.hpp"
#include "hashinterface.hpp"
#include "mathinterface.hpp"
#include "randominterface.hpp"
#include "srpverificator.hpp"

#include "ng.hpp"

namespace Dsrp
{
	class SrpServer
	{	
		public:
			SrpServer(LookupInterface &lookupInterface, MathInterface &mathInterface, RandomInterface &randomInterface);
			SrpVerificator getVerificator(const bytes &username, const bytes &AA);
			
			
		private:
			LookupInterface &lookup;
			MathInterface &math;
			RandomInterface &random;
	};
}


#endif
