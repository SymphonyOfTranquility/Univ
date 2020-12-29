#pragma once
#include "SubWindowView.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

class WorkWithWindow
{
	shared_ptr<RenderWindow> window;
	vector<shared_ptr<SubWindowView> > subWindowsView;

	string information;

	void draw();
public:
	WorkWithWindow(string fileName);
	void work();
	bool isOpen();
	~WorkWithWindow();
};

