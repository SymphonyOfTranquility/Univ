#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

struct TcharacteristicOfButton
{
	string name;

	int posWidth, posHeight, width, height;
	bool pressed, released, underCursor;
};

class Button
{
	TcharacteristicOfButton button;
public:
	Button(ifstream &fin);
	Vector2f getPosition();
	Vector2i getSize();
	bool isPressed();
	bool isUnderMouse(Vector2i posMouse);
	void setPressed();
	void dePressed();
	void setReleased();
	bool isReleased();
	void deReleased();
	void setUnderCursor();
	bool isUnderCursor();
	void deUnderCursor();
	string getName();
	~Button();
};

