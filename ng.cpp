
#include "ng.hpp"

namespace Dsrp
{

	template<class HashFunctionPolicy>
	Ng<HashFunctionPolicy>::Ng
	(bytes NN, bytes gg)
	{
		N = NN;
		g = gg;
	}
	
	template<class HashFunctionPolicy>
	Ng<HashFunctionPolicy>::Ng
	(Ng& copy)
	{
		copy.N = N;
		copy.g = g;
	}
	
	template<class HashFunctionPolicy>
	bytes Ng<HashFunctionPolicy>::getN()
	{
		return N;
	}
	
	template<class HashFunctionPolicy>
	bytes Ng<HashFunctionPolicy>::getg()
	{
		return g;
	}
	
	template<class HashFunctionPolicy>
	bytes Ng<HashFunctionPolicy>::getk()
	{
		return k;
	}
	
	template<class HashFunctionPolicy>
	static Ng Ng<HashFunctionPolicy>::predefined
	(unsigned int bits)
	{
		
	}
	
	
	template<class HashFunctionPolicy>
	void Ng<HashFunctionPolicy>::calculateMultiplier()
	{
		HashFunctionPolicy hf;
		bytes NNgg = N;
		NNgg.insert(NNgg.end(), g.begin(), g.end());
		k = hf.hash(NNgg);
	}
}
