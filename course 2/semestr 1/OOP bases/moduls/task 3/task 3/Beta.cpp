#include "Beta.h"



Beta::Beta()
{
	N = beta_size;
	++beta_size;
}


Beta::~Beta()
{
	S = S - N;
}
