#include "ListView.h"

void ListView::inputColor(ifstream &fin, shared_ptr<Color> color)
{
	int red, green, blue, transparent;
	fin >> red >> green >> blue >> transparent;
	color.get()->b = blue;
	color.get()->r = red;
	color.get()->g = green;
	color.get()->a = transparent;
}

void ListView::makeFrame(Vector2i size)
{
	listFrame = shared_ptr<VertexArray>(new VertexArray);
	shared_ptr<Vertex> tempVertex = shared_ptr<Vertex>(new Vertex);
	Vector2f tempPos =Vector2f(0.5f, 0.5f);
	tempVertex.get()->color = *colorFrame;
	tempVertex.get()->position = tempPos;
	listFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = *colorFrame;
	tempPos.x = size.x - 0.5f;
	tempVertex.get()->position = tempPos;
	listFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = *colorFrame;
	tempPos.y = size.y - 0.5f;
	tempVertex.get()->position = tempPos;
	listFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = *colorFrame;
	tempPos.x = 0.5f;
	tempVertex.get()->position = tempPos;
	listFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = *colorFrame;
	tempPos.y = 0.5f;
	tempVertex.get()->position = tempPos;
	listFrame.get()->append(*tempVertex);

	listFrame.get()->setPrimitiveType(LinesStrip);
}

ListView::ListView(ifstream &fin, shared_ptr<List> curList)
{
	list = curList;

	renderListView = shared_ptr<RenderTexture>(new RenderTexture);
	Vector2i listSize = list.get()->getListSize();
	renderListView.get()->create(listSize.x, listSize.y);
	spriteListView = shared_ptr<Sprite>(new Sprite);
	spriteListView.get()->setPosition(list.get()->getListPosition());
//background
	colorBackground = shared_ptr<Color>(new Color);
	inputColor(fin, colorBackground);
//frame
	colorFrame = shared_ptr<Color>(new Color);
	inputColor(fin, colorFrame);
	colorFrameChosen = shared_ptr<Color>(new Color);
	inputColor(fin, colorFrameChosen);
	
	makeFrame(list.get()->getListSize());
///element
//background 
	renderElemBackground = shared_ptr<RenderTexture>(new RenderTexture);
	Vector2i elemSize = list.get()->getElemSize();
	renderElemBackground.get()->create(elemSize.x, elemSize.y);
	renderElemBackground.get()->clear(Color::White);

	colorElemBackground = shared_ptr<Color>(new Color);
	inputColor(fin, colorElemBackground);
	colorElemBackgroundUnderCursor = shared_ptr<Color>(new Color);
	inputColor(fin, colorElemBackgroundUnderCursor);
	colorElemBackgroundChosen = shared_ptr<Color>(new Color);
	inputColor(fin, colorElemBackgroundChosen);

	spriteElemBackground = shared_ptr<Sprite>(new Sprite);
	spriteElemBackground.get()->setTexture(renderElemBackground.get()->getTexture());

//text
	font = shared_ptr<Font>(new Font);
	font.get()->loadFromFile("Data\\Inconsolata.ttf");
	listText = shared_ptr<Text>(new Text);
	int sizeText;
	fin >> sizeText;
	listText.get()->setFont(*font);
	listText.get()->setCharacterSize(sizeText);

	colorText = shared_ptr<Color>(new Color);
	inputColor(fin, colorText);

///slider
	shared_ptr<Button> tempButton = list.get()->getSliderButton();
	slider = shared_ptr<ButtonView>(new ButtonView(fin, tempButton));
	renderSliderField = shared_ptr<RenderTexture>(new RenderTexture);
	Vector2i sliderSize = list.get()->getSliderFieldSize();
	renderSliderField.get()->create(sliderSize.x, sliderSize.y);
	renderSliderField.get()->clear(Color::White);

	colorSliderBackground = shared_ptr<Color>(new Color);
	inputColor(fin, colorSliderBackground);
	
	spriteSliderBackground = shared_ptr<Sprite>(new Sprite);
	Vector2f sliderPos = list.get()->getSliderFieldPos();
	spriteSliderBackground.get()->setTexture(renderSliderField.get()->getTexture());
	spriteSliderBackground.get()->setPosition(sliderPos);
	spriteSliderBackground.get()->setColor(*colorSliderBackground);
}

void ListView::draw(shared_ptr<RenderTexture> &window)
{
	renderListView.get()->clear(*colorBackground);
	renderListView.get()->draw(*spriteSliderBackground);
	slider.get()->draw(renderListView);
	renderListView.get()->draw(*listFrame);
	renderListView.get()->display();
	spriteListView.get()->setTexture(renderListView.get()->getTexture());

	window.get()->draw(*spriteListView);
}


ListView::~ListView()
{
}
