#include "Delta.h"



Delta::Delta()
{
	N = delta_size;
	++delta_size;
}


Delta::~Delta()
{
	S = S + 3 * N - 41;
}
