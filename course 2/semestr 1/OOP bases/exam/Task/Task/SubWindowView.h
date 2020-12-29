#pragma once
#include "SubWindow.h"
#include "ButtonView.h"
#include "ListView.h"

class SubWindowView
{
	shared_ptr<SubWindow> subWindow;
	vector<shared_ptr<ButtonView> > buttons;
	vector<shared_ptr<ListView> > lists;

	Vector2i prevMousePos;
	bool background;
	shared_ptr<Texture> backgroundTexture;
	shared_ptr<Sprite> backgroundSprite;

	shared_ptr<RenderTexture> renderSubWindow;
	shared_ptr<Sprite> spriteSubWindow;
	shared_ptr<Color> backgroundWindowColor;
	shared_ptr<VertexArray> subWindowFrame;

	string newWindow;
	string textForEnd;

	void checkButtonIsPressed(shared_ptr<RenderWindow> &window, Vector2i mousePos, bool checkPressed);
	void checkButtonIsReleased(shared_ptr<RenderWindow> &window, Vector2i mousePos);
	void checkButtonIsUnderCursor(shared_ptr<RenderWindow> &window, Vector2i mousePos);
public:
	SubWindowView(ifstream &fin);
	void draw(shared_ptr<RenderWindow> &window);
	bool isActive();
	void setActive(string created);
	void setFocus();
	void deFocus();
	string hasParent();
	string needNewWindow();
	string getName();
	void pollEvent(Event event, shared_ptr<RenderWindow> &window);
	void withoutEventButton(shared_ptr<RenderWindow> &window);
	void setText(string text);

	~SubWindowView();
};

