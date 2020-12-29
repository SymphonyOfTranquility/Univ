#include "AlgoObject.h"



AlgoObject::AlgoObject(ifstream &fin)
{
	fin >> name;
	int n;
	fin >> n;
	string s;
	for (int i = 0; i < n; ++i) 
	{
		fin >> s; 
		features.push_back(s);
	}	
}

int AlgoObject::getRandomFeature()
{
	return rand()%features.size();
}

AlgoObject::~AlgoObject()
{
}
