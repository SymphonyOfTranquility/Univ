#pragma once
#include "SubWindow.h"
#include "BoardView.h"
#include "ButtonView.h"

class SubWindowView
{
	shared_ptr<SubWindow> subWindow;
	vector<shared_ptr<ButtonView> > buttons;

	Vector2i prevMousePos;
	bool background;
	shared_ptr<Texture> backgroundTexture;
	shared_ptr<Sprite> backgroundSprite;

	shared_ptr<RenderTexture> renderSubWindow;
	shared_ptr<Sprite> spriteSubWindow;
	shared_ptr<Color> backgroundWindowColor;
	shared_ptr<VertexArray> subWindowFrame;

	string newWindow;

	void checkButtonIsPressed(shared_ptr<RenderWindow> &window, Vector2i mousePos, bool checkPressed);
	void checkButtonIsReleased(shared_ptr<RenderWindow> &window, Vector2i mousePos, shared_ptr<BoardView> &board);
	void checkButtonIsUnderCursor(shared_ptr<RenderWindow> &window, Vector2i mousePos);
public:
	SubWindowView(ifstream &fin);
	void draw(shared_ptr<RenderWindow> &window);
	bool isActive();
	void setActive(string created);
	void setFocus();
	bool hasFocus();
	void deFocus();
	string hasParent();
	string needNewWindow();
	string getName();
	void pollEvent(Event event, shared_ptr<RenderWindow> &window, shared_ptr<BoardView> &board);
	void withoutEventButton(shared_ptr<RenderWindow> &window);
	void setText(string text);
	void setRect(Figure::Colour colour);
	~SubWindowView();
};

