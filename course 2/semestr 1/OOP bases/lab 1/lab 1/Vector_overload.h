#ifndef _VECTOR_OVERLOAD_H_USED
#define _VECTOR_OVERLOAD_H_USED

#include <iostream>
#include <vector>

using std::istream;
using std::ostream;
using std::vector;

template<typename T>
istream& operator>>(istream& is, vector<T>& v)
{
	int n;
	T cur;
	is >> n;
	for (int i = 0; i < n; ++i) {
		is >> cur;
		v.push_back(cur);
	}
	return is;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << "( ";
	if (v.size() != 0)
		os << v[0];
	for (size_t i = 1; i < v.size(); ++i)
		os << "; " << v[i];
	os << " )";
	return os;
}

#endif