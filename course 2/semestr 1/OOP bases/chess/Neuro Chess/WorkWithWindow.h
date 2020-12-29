#pragma once

#include "BoardView.h"
#include "SubWindowView.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace sf;
using namespace std;

class WorkWithWindow
{
	shared_ptr<RenderWindow> window;
	shared_ptr<BoardView> board;
	vector<shared_ptr<SubWindowView> > subWindowsView;

	string information;
	int glob;
	void draw();

public:
	WorkWithWindow(string fileName);
	void work();
	bool isOpen();
	~WorkWithWindow();
};

