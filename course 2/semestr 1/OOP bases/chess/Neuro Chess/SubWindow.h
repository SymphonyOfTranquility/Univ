#pragma once
#include "Button.h"

#include <vector>

using namespace std;

class SubWindow
{
	vector<shared_ptr<Button> > allButtons;

	string name;
	string whoCreated;
	bool haveToUpdateBoard;
	int posHeight, posWidth, height, width;
	bool active, focus;

public:
	SubWindow(ifstream &fin);
	vector<shared_ptr<Button> > getAllButtons();
	string getName();
	Vector2i getSize();
	Vector2f getPosition();
	bool isActive();
	void setActive(string created = "");
	void deActive();
	bool hasFocus();
	void setFocus();
	void deFocus();
	string hasParent();
	bool checkButtonIsPressed(Vector2i mousePos);
	bool checkButtonIsReleased(Vector2i mousePos);
	bool checkButtonIsUnderCursor(Vector2i mousePos);
	~SubWindow();
};

