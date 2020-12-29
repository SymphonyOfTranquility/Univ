#include "AlgoImage.h"

int AlgoImage::curId = 0;

void AlgoImage::createName()
{
	ifstream fin("Data\\namePictures.txt");
	int namePos = rand() % 100;
	for (int i = 0; i < namePos + 1; ++i)
		getline(fin, name);
	fin.close();
}


AlgoImage::AlgoImage(shared_ptr<VectorAlgoObjects> allObj)
{
	createName();

	timeCreation = rand() % 2000;
	id = curId;
	++curId;
	heightPixels = 200 + rand() % 3800;
	widthPixels = 200 + rand() % 3800;

	int minSize = 25;
	int maxSizeHeight = (int)log(heightPixels);
	maxSizeHeight *= maxSizeHeight * maxSizeHeight;
	int maxSizeWidth = (int)log(widthPixels);
	maxSizeWidth *= maxSizeWidth * maxSizeWidth;
	int areaSize = heightPixels * widthPixels;
	int curSize = 0, randObj, randFeat;
	Vector2i tempSize, tempPos;
	while (areaSize * 15 / 16 < curSize)
	{
		randObj = allObj.get()->getRandomObject();
		randFeat = allObj.get()->getRandomFeature(randObj);
		indexObjects.push_back(randObj);
		typeObject.push_back(randFeat);
		tempSize = Vector2i(rand() % (maxSizeHeight - minSize) + minSize, rand() % (maxSizeWidth - minSize) + minSize);
		tempPos = Vector2i(rand() % heightPixels, rand() % widthPixels);
		curSize += tempSize.x * tempSize.y;
		posObjects.push_back(tempPos);
		sizeObjects.push_back(tempSize);
	}
}

AlgoImage::~AlgoImage()
{
}
