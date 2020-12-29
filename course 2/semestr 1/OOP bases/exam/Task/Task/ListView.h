#pragma once
#include "ButtonView.h"
#include "List.h"

class ListView
{
	shared_ptr<List> list;

///general about list
	shared_ptr<RenderTexture> renderListView;
	shared_ptr<Sprite> spriteListView;
//background
	shared_ptr<Color> colorBackground;
//frame
	shared_ptr<Color> colorFrame, colorFrameChosen;
	shared_ptr<VertexArray> listFrame;

///elements
//background
	shared_ptr<RenderTexture> renderElemBackground;
	shared_ptr<Color> colorElemBackground, colorElemBackgroundUnderCursor, colorElemBackgroundChosen;
	shared_ptr<Sprite> spriteElemBackground;
//text
	shared_ptr<Text> listText;
	shared_ptr<Font> font;
	shared_ptr<Color> colorText;

///slider
	shared_ptr<ButtonView> slider;
	shared_ptr<RenderTexture> renderSliderField;
	shared_ptr<Color> colorSliderBackground;
	shared_ptr<Sprite> spriteSliderBackground;

	void inputColor(ifstream & fin, shared_ptr<Color> color);
	void makeFrame(Vector2i size);
public:
	ListView(ifstream &fin, shared_ptr<List> curList);
	void draw(shared_ptr<RenderTexture> &window);
	~ListView();
};

