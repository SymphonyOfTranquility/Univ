#pragma once
#include "Figure.h"

#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;
using namespace sf;

const int PIXEL_SIZE = 64;

class FigureView
{
	shared_ptr<Figure> figure;
	Vector2i posInTexture;
	Vector2f posInWindow;

public:
	FigureView(shared_ptr<Figure> figure);
	Vector2i getPosInTexture();
	Vector2f getPosInWindow();

	bool isUnderMouse(Vector2i mousePos);
	void setMousePosition(Vector2i mousePos);
	void setCellPosition(Vector2i mousePos);
	void setCellPrevPosition();
	void setPosition(Vector2f pos);
	int getFigureColorId();
	shared_ptr<Figure> getFigure();
	void setType(Figure::Type curType);

	~FigureView();
};

