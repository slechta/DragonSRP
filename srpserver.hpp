
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
			SrpServer(LookupInterface &lookupInterface,
					  MathInterface &mathInterface,
					  RandomInterface &randomInterface)	:
						lookup(lookupInterface),
						math(mathInterface),
						random(randomInterface)
					  
			{
			
			}			
			
			/*
			SrpVerificator getVerificator(const bytes &username, const bytes &AA)
			{
				// check status of authentification
				User usr = this->getByName(username);
				bytes M1, M2, K;
				//serverChallange(username, usr.getSalt(), usr.getVerificator(), AA, 
				
				return 0;
			}
			*/
			
			
		private:
			LookupInterface &lookup;
			MathInterface &math;
			RandomInterface &random;
	};
}


#endif
