#include "Prime_numbers.h"

vector<int> primes;

void resheto()
{
	const int nmax = 2000;
	primes.clear();
	bool used[nmax + 1];
	for (int i = 0; i <= nmax; ++i)
		used[i] = false;
	for (int i = 2; i <= nmax; ++i) {
		if (!used[i]) 
		{
			primes.push_back(i);
			for (int j = i * i; j <= nmax; j += i)
				used[j] = true;
		}
	}
}

