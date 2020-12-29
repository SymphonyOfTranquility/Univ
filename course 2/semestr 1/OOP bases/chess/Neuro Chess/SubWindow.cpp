#include "SubWindow.h"



SubWindow::SubWindow(ifstream &fin)
{
	getline(fin, name);
	while (name == "")
		getline(fin, name);
	fin >> posHeight >> posWidth;
	fin >> height >> width;
	active = false;
	string dataForButtons;
	getline(fin, dataForButtons);
	while (dataForButtons == "")
		getline(fin, dataForButtons);

	ifstream ffin(dataForButtons);
	int numberOfButtons;
	ffin >> numberOfButtons;
	shared_ptr<Button> tempButton;
	for (int i = 0; i < numberOfButtons; ++i)
	{
		tempButton = shared_ptr<Button>(new Button(ffin));
		allButtons.push_back(tempButton);
	}
	ffin.close();

	active = false;// = needToDraw = false;
}

vector<shared_ptr<Button>> SubWindow::getAllButtons()
{
	return allButtons;
}

string SubWindow::getName()
{
	return name;
}

Vector2i SubWindow::getSize()
{
	return Vector2i(width, height);
}

Vector2f SubWindow::getPosition()
{
	return Vector2f(float(posWidth), float(posHeight));
}

//bool SubWindow::getNeedToDraw()
//{
//	return needToDraw;
//}

bool SubWindow::isActive()
{
	return active;
}

void SubWindow::setActive(string created)
{
	active = true;
	//needToDraw = true;
	whoCreated = created;
}

void SubWindow::deActive()
{
	active = false;
	focus = false;
}

bool SubWindow::hasFocus()
{
	return focus;
}

void SubWindow::setFocus()
{
	focus = true;
}

void SubWindow::deFocus()
{
	focus = false;
}

string SubWindow::hasParent()
{
	string temp = whoCreated;
	whoCreated = "";
	return temp;
}

bool SubWindow::checkButtonIsPressed(Vector2i mousePos)
{
	mousePos -= Vector2i{ posWidth, posHeight };

	for (int i = 0; i < (int)allButtons.size(); ++i)
	{
		if (allButtons[i].get()->isUnderMouse(mousePos))
		{
			allButtons[i].get()->setPressed();
			return true;
		}
	}
	return false;
}

bool SubWindow::checkButtonIsReleased(Vector2i mousePos)
{
	mousePos -= Vector2i{ posWidth, posHeight };

	for (int i = 0; i < (int)allButtons.size(); ++i)
	{
		if (allButtons[i].get()->isUnderMouse(mousePos) && allButtons[i].get()->isPressed())
		{
			allButtons[i].get()->dePressed();
			allButtons[i].get()->setReleased();
			return true;
		}
	}
	return false;
}


bool SubWindow::checkButtonIsUnderCursor(Vector2i mousePos)
{
	mousePos -= Vector2i{ posWidth, posHeight };

	bool ok = false;
	for (int i = 0; i < (int)allButtons.size(); ++i)
	{
		if (allButtons[i].get()->isUnderMouse(mousePos))
		{
			allButtons[i].get()->setUnderCursor();
			//		cout << allButtons[i].get()->getName() << '\n';
			ok = true;
		}
		else
			allButtons[i].get()->deUnderCursor();
	}
	return ok;
}


SubWindow::~SubWindow()
{
}
