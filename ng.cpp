
#include "ng.hpp"

namespace Dsrp
{
	Ng::Ng(bytes NN, bytes gg)
	{
		N = NN;
		g = gg;
	}
		
	Ng::Ng(Ng& copy)
	{
		copy.N = N;
		copy.g = g;
	}
	
	bytes Ng::getN()
	{
		return N;
	}
	
	bytes Ng::getg()
	{
		return g;
	}
}
