
#include "mathinterface.hpp"

namespace Dsrp
{
	MathInterface::MathInterface(HashInterface &hashInterface)
		: hash(hashInterface)
	{
		
	}
	
	MathInterface::~MathInterface()
	{
		// emtpy
	}
}
