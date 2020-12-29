#include "HashFunctions.h"

int firstHash(string s, int ssid)
{
	int ans = 0;
	for (int i = 0; i < (int)s.length(); ++i)
		ans = (s[i] ^ ans + s.length()) % ssid;
	while(ans < 0)
		ans = (ans + ssid) % ssid;
	return ans;
}

int secondHash(string s, int ssid)
{
	long long ans = 0, p = 257, step = 1, mod = ssid;
	for (int i = 0; i < (int)s.length(); ++i) 
	{
		ans = ((s[i] * step)%mod + ans + s[i]^mod) % mod;
		step = (step*p)%mod;
	}
	while (ans < 0)
		ans = (ans + mod)%mod;
	return (int)ans;
}
