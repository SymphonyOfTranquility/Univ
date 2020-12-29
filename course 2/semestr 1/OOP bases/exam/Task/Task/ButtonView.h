#pragma once
#include "Button.h"

#include <SFML/Graphics.hpp>

using namespace sf;

class ButtonView
{
	shared_ptr<Button> button;

	bool texture;
	shared_ptr<Texture> buttonTexture;
	shared_ptr<Sprite> sprite;

	bool background;
	shared_ptr<RenderTexture> renderBackground;
	shared_ptr<Color>  colorBackground, colorBackgroundPressed, colorBackgroundUnderCursor;

	bool frame;
	shared_ptr<Color> colorFrame, colorFramePressed, colorFrameUnderCursor;
	shared_ptr<VertexArray> buttonFrame;

	bool text;
	shared_ptr<Text> buttonText;
	shared_ptr<Font> font;
	shared_ptr<Color> colorText;

public:
	ButtonView(ifstream &fin, shared_ptr<Button> curButton);
	void draw(shared_ptr<RenderTexture> &window);
	string getName();
	bool isPressed();
	void dePressed();
	bool isReleased();
	void deReleased();
	bool isUnderCursor();
	void deUnderCursor();
	void setText(string curText);

	~ButtonView();
};

