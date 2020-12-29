#include "Button.h"



Button::Button(ifstream &fin)
{
	getline(fin, button.name);
	while (button.name == "")
		getline(fin, button.name);
	fin >> button.posHeight >> button.posWidth;
	fin >> button.height >> button.width;
	button.pressed = button.released = button.underCursor = false;
}

Vector2f Button::getPosition()
{
	return Vector2f(float(button.posWidth), float(button.posHeight));
}

Vector2i Button::getSize()
{
	return Vector2i(button.width, button.height);
}

bool Button::isPressed()
{
	return button.pressed;
}

bool Button::isUnderMouse(Vector2i posMouse)
{
	return (button.posWidth <= posMouse.x && posMouse.x <= button.posWidth + button.width &&
		button.posHeight <= posMouse.y && posMouse.y <= button.posHeight + button.height);
}

void Button::setPressed()
{
	button.pressed = true;
}

void Button::dePressed()
{
	button.pressed = false;
}

void Button::setReleased()
{
	button.released = true;
}

bool Button::isReleased()
{
	return button.released;
}

void Button::deReleased()
{
	button.released = false;
}

void Button::setUnderCursor()
{
	button.underCursor = true;
}

bool Button::isUnderCursor()
{
	return button.underCursor;
}

void Button::deUnderCursor()
{
	button.underCursor = false;
}

string Button::getName()
{
	return button.name;
}


Button::~Button()
{
}
