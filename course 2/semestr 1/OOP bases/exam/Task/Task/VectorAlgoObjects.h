#pragma once
#include "AlgoObject.h"

#include <fstream>
#include <vector>

using namespace std;

class VectorAlgoObjects
{
	vector<shared_ptr<AlgoObject> > objects;
	bool afterAlgo;

public:
	VectorAlgoObjects(ifstream &fin);
	int getRandomObject();
	int getRandomFeature(int numberObject);
	~VectorAlgoObjects();
};

