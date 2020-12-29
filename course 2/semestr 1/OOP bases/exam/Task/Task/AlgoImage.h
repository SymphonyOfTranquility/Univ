#pragma once
#include "VectorAlgoObjects.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;
using namespace sf;

class AlgoImage
{
	static int curId;
	string name;
	int timeCreation;
	int id;
	int heightPixels, widthPixels;
	
	vector<int> indexObjects;
	vector<int> typeObject;
	vector<Vector2i> posObjects;
	vector<Vector2i> sizeObjects;

	void createName();
public:
	AlgoImage(shared_ptr<VectorAlgoObjects> allObj);
	~AlgoImage();
};

