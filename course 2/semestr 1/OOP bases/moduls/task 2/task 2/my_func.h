#pragma once
#include <cmath>
#include <string>


using std::string;

const int RETURN_EXP = 8941;

template <typename T>
int my_func(T value);

int factorial(int a,int mod)
{
	int step = 1;
	for (int i = 1; i <= a; ++i)
		step = (step*i)%mod;
	return step;
}

template<>
int my_func(int value)			//for integers
{
	int mod, ans;
	if (value > 0) 
	{
		mod = 141;
		ans = (factorial(value, mod) + value - 1) % mod;
	}
	else if (value < 0) 
	{
		mod = 241;
		value %= mod;
		ans = value * value * value % mod;
	}
	else 
		return RETURN_EXP;
	while (ans < 0)
		ans += mod;
	return ans;
}

template<>
int my_func(double value)
{
	int ans = (int) round(1.0 / sin(77 * value));
	ans %= 341;
	return ans;
}

template<>
int my_func(string value)
{
	int ans = 0;
	for (int i = 0; i < value.length(); ++i)
		if (value[i] > 64 && value[i] < 91)
			++ans;
	return ans;
}

template<typename T>
int my_func(T value)
{
	return RETURN_EXP;
}