#include "Alpha.h"

#include <iostream>

Alpha::Alpha()
{
	N = alpha_size;
	++alpha_size;
}


Alpha::~Alpha()
{
	S = S - 2 * N + 14;
	cout << N << ' ' << S << '\n';
}
