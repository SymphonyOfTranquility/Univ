#pragma once
#include "Triangle.h"
#include "Tetragon.h"
#include "Pentagon.h"

#include <random>
#include <string>
#include <vector>

using std::string;
using std::vector;

template<typename T>
T getrandom(T value);

template<>
inline int getrandom(int value)
{
	return rand() % 200 - 100;
}

template<>
inline double getrandom(double value)
{
	return (double)rand() / RAND_MAX * 200.0 - 100;
}

template<>
inline string getrandom(string value)
{
	int len = rand()%30;
	value = "";
	for (int i = 0; i < len; ++i)
	{
		char c = rand() % 26+'a';
		value += c;
	}
	return value;
}

template<>
inline Triangle getrandom(Triangle value)
{
	value.my_rand();
	return value;
}

template<>
inline Tetragon getrandom(Tetragon value)
{
	value.my_rand();
	return value;
}

template<>
inline Pentagon getrandom(Pentagon value)
{
	value.my_rand();
	return value;
}

template<typename T>
inline vector<T> getrandom(vector<T> value)
{
	int len = rand() % 30;
	value.clear();
	for (int i = 0; i < len; ++i)
	{
		T *cur = new T;
		value.push_back(getrandom(*cur));
	}
	return value;
}



