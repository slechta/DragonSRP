
#include "mathinterface.hpp"

namespace Dsrp
{
	MathInterface::MathInterface(HashInterface &hashInterface, Ng ngVal)
		: hash(hashInterface),
		  ng(ngVal)
	{
		
	}
	
	// Virtual destructor
	MathInterface::~MathInterface()
	{
		// emtpy
	}
}
