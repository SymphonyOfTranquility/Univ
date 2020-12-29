#pragma once
#include "AlgoObject.h"
#include "AlgoImage.h"
#include "Button.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

struct TcharacteristicOfList
{
	string name;

	int posWidth, posHeight, width, height;
	bool pressed, released, underCursor;
};

class List
{
	TcharacteristicOfList list;

	bool needSlider;
	shared_ptr<Button> slider;
	int sliderFieldWidth, sliderFieldHeight, sliderFieldPosWidth, sliderFieldPosHeight;
	int elemWidth, elemHeight, elemInterval;
	int index;

	shared_ptr<VectorAlgoObjects> allObjects;
	vector<pair<int, shared_ptr<AlgoImage> > > images;


public:
	List(ifstream &fin);
	Vector2f getListPosition();
	Vector2i getListSize();

	bool isUnderMouse(Vector2i posMouse);
	bool isSliderUnderMouse(Vector2i posMouse);

	shared_ptr<Button> getSliderButton();
	Vector2f getSliderPosition();
	Vector2i getSliderSize();
	bool isSliderPressed();
	void setSliderPressed();
	void deSliderPressed();
	void setSliderUnderCursor();
	bool isSliderUnderCursor();
	void deSliderUnderCursor();
	Vector2i getSliderFieldSize();
	Vector2f getSliderFieldPos();

	Vector2i getElemSize();
	void setElemReleased();
	bool isElemReleased();
	void deElemReleased();
	void setElemUnderCursor();
	bool isElemUnderCursor();
	void deElemUnderCursor();

	string getName();
	~List();
};

