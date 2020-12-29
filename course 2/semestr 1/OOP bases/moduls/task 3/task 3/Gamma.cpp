#include "Gamma.h"



Gamma::Gamma()
{
	N = gamma_size;
	++gamma_size;
}


Gamma::~Gamma()
{
	S = S - N;
}
