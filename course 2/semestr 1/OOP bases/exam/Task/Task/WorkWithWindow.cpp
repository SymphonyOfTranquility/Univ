#include "WorkWithWindow.h"



void WorkWithWindow::draw()
{
	if (window.get()->isOpen())
	{
		window.get()->clear(Color(0, 0, 0, 0));
		for (int i = 0; i < (int)subWindowsView.size(); ++i)
			subWindowsView[i].get()->draw(window);
		window.get()->display();
	}
}

WorkWithWindow::WorkWithWindow(string fileName)
{
	information = fileName;
	ifstream fin(fileName);
	string windowName;
	getline(fin, windowName);
	int height, width;
	fin >> width >> height;
	window = shared_ptr<RenderWindow>(new RenderWindow(VideoMode(height, width), windowName, Style::None));

	int numberOfWindows;
	shared_ptr<SubWindowView> temp;
	fin >> numberOfWindows;
	for (int i = 0; i < numberOfWindows; ++i)
	{
		temp = shared_ptr<SubWindowView>(new SubWindowView(fin));
		subWindowsView.push_back(temp);
	}
	fin.close();
}

void WorkWithWindow::work()
{
	Event event;
	if (window.get()->pollEvent(event))
	{
		if (window.get()->hasFocus())
		{
			for (int i = 0; i < (int)subWindowsView.size(); ++i)
			{
				if (subWindowsView[i].get()->isActive())
				{
					subWindowsView[i].get()->pollEvent(event, window);
					string temp = subWindowsView[i].get()->needNewWindow();
					if (temp != "")
					{
						for (int j = 0; j < (int)subWindowsView.size(); ++j)
						{
							if (subWindowsView[j].get()->getName() == temp)
							{
								subWindowsView[j].get()->setActive(subWindowsView[i].get()->getName());
								subWindowsView[j].get()->setFocus();
								subWindowsView[i].get()->deFocus();
								break;
							}
						}
					}
				}
			}
		}
	}
	
	
	for (int i = 0; i < (int)subWindowsView.size(); ++i)
	{
		if (subWindowsView[i].get()->isActive())
			subWindowsView[i].get()->withoutEventButton(window);	
	}

	draw();
}

bool WorkWithWindow::isOpen()
{
	return window.get()->isOpen();
}


WorkWithWindow::~WorkWithWindow()
{
}
