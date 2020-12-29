#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class AlgoObject
{
	string name;
	vector<string> features; 

public:
	AlgoObject(ifstream &fin);
	//AlgoObject(shared_ptr<AlgoObject> copy);
	int getRandomFeature();
	~AlgoObject();
};

