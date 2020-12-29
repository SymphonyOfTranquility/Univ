#include "VectorAlgoObjects.h"



VectorAlgoObjects::VectorAlgoObjects(ifstream &fin)
{
	int n;
	fin >> n;
	shared_ptr<AlgoObject> tempObject;
	for (int i = 0; i < n; ++i)
	{
		tempObject = shared_ptr<AlgoObject>(new AlgoObject(fin));
		objects.push_back(tempObject);
	}
	afterAlgo = false;
}

int VectorAlgoObjects::getRandomObject()
{
	return rand() % objects.size();
}

int VectorAlgoObjects::getRandomFeature(int numberObject)
{
	return objects[numberObject].get()->getRandomFeature();
}


VectorAlgoObjects::~VectorAlgoObjects()
{
}
