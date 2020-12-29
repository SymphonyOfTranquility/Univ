#include "List.h"



List::List(ifstream &fin)
{
	getline(fin, list.name);
	while (list.name == "")
		getline(fin, list.name);
	fin >> list.posHeight >> list.posWidth;					//pos list
	fin >> list.height >> list.width;						//size list
	list.pressed = list.released = list.underCursor = false;
	
	needSlider = false;
	slider = shared_ptr<Button>(new Button(fin));			//slider button
	fin >> sliderFieldHeight >> sliderFieldWidth;			//slider field size
	fin >> sliderFieldPosHeight >> sliderFieldPosWidth;		//slider field pos

	fin >> elemHeight >> elemWidth >> elemInterval;			//element size
	
	bool ok;
	fin >> ok;
	if (ok)
	{
		ifstream ffin("Data\\object names.dat");
		allObjects = shared_ptr<VectorAlgoObjects>(new VectorAlgoObjects(ffin));	
		ffin.close();
	}
	index = -1;
}

Vector2f List::getListPosition()
{
	return Vector2f(float(list.posWidth), float(list.posHeight));
}

Vector2i List::getListSize()
{
	return Vector2i(list.width, list.height);
}

shared_ptr<Button> List::getSliderButton()
{
	return slider;
}

Vector2f List::getSliderPosition()
{
	return slider.get()->getPosition();
}

Vector2i List::getSliderSize()
{
	return  slider.get()->getSize();
}

bool List::isSliderPressed()
{
	return slider.get()->isPressed();
}

bool List::isUnderMouse(Vector2i posMouse)
{
	return (list.posWidth <= posMouse.x && posMouse.x <= list.posWidth + list.width &&
		list.posHeight <= posMouse.y && posMouse.y <= list.posHeight + list.height);
}

bool List::isSliderUnderMouse(Vector2i posMouse)
{
	return slider.get()->isUnderMouse(posMouse);
}

void List::setSliderPressed()
{
	slider.get()->setPressed();
}

void List::deSliderPressed()
{
	slider.get()->dePressed();
}

void List::setSliderUnderCursor()
{
	slider.get()->setUnderCursor();
}

bool List::isSliderUnderCursor()
{
	return slider.get()->isUnderCursor();
}

void List::deSliderUnderCursor()
{
	return slider.get()->deUnderCursor();
}

Vector2i List::getSliderFieldSize()
{
	return Vector2i(sliderFieldWidth, sliderFieldHeight);
}

Vector2f List::getSliderFieldPos()
{
	return Vector2f(sliderFieldPosWidth, sliderFieldPosHeight);
}

Vector2i List::getElemSize()
{
	return Vector2i(elemWidth,elemHeight);
}

void List::setElemReleased()
{
	list.released = true;
}

bool List::isElemReleased()
{
	return list.released;
}

void List::deElemReleased()
{
	list.released = false;
}

void List::setElemUnderCursor()
{
	list.underCursor = true;
}

bool List::isElemUnderCursor()
{
	return list.underCursor;
}

void List::deElemUnderCursor()
{
	list.underCursor = false;
}

string List::getName()
{
	return list.name;
}


List::~List()
{
}
