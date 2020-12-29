#pragma once
#include "Button.h"
#include "List.h"

#include <vector>

using namespace std;

class SubWindow
{
	vector<shared_ptr<Button> > allButtons;
	vector<shared_ptr<List> > allLists;

	string name;
	string whoCreated;

	int posHeight, posWidth, height, width;
	bool active, focus;

public:
	SubWindow(ifstream &fin);
	vector<shared_ptr<Button> > getAllButtons();
	vector<shared_ptr<List> > getAllLists();
	string getName();
	Vector2i getSize();
	Vector2f getPosition();
	bool isActive();
	void setActive(string created = "");
	void deActive();
	bool hasFocus();
	void setFocus();
	void deFocus();;
	string hasParent();
	bool checkButtonIsPressed(Vector2i mousePos);
	bool checkButtonIsReleased(Vector2i mousePos);
	bool checkButtonIsUnderCursor(Vector2i mousePos);
	~SubWindow();
};

