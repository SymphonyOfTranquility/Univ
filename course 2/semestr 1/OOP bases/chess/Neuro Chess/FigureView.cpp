#include "FigureView.h"


FigureView::FigureView(shared_ptr<Figure> figure) : figure(figure)
{
	posInTexture.x = (figure.get()->getTypeId() - 1);
	posInTexture.y = (figure.get()->getColourId() / 128);
	posInTexture *= int(PIXEL_SIZE);
	Vector2i temp = figure.get()->getPosition();
	temp *= PIXEL_SIZE;
	posInWindow = Vector2f(temp);
	swap(posInWindow.x, posInWindow.y);
}

Vector2i FigureView::getPosInTexture()
{
	return posInTexture;
}

Vector2f FigureView::getPosInWindow()
{
	return posInWindow;
}

bool FigureView::isUnderMouse(Vector2i mousePos)
{
	if (posInWindow.x <= mousePos.x && mousePos.x < posInWindow.x + PIXEL_SIZE
		&& posInWindow.y <= mousePos.y && mousePos.y < posInWindow.y + PIXEL_SIZE)
		return true;
	else
		return false;
}

void FigureView::setMousePosition(Vector2i mousePos)
{
	mousePos -= Vector2i(PIXEL_SIZE / 2, PIXEL_SIZE / 2);
	mousePos.x = min(max(-PIXEL_SIZE / 8, mousePos.x), PIXEL_SIZE*(BOARD_SIZE - 1) + PIXEL_SIZE / 8);
	mousePos.y = min(max(-PIXEL_SIZE / 8, mousePos.y), PIXEL_SIZE*(BOARD_SIZE - 1) + PIXEL_SIZE / 8);
	posInWindow = Vector2f(mousePos);
}

void FigureView::setCellPosition(Vector2i mousePos)
{
	mousePos /= PIXEL_SIZE;
	mousePos *= PIXEL_SIZE;
	posInWindow = Vector2f(mousePos);
}

void FigureView::setCellPrevPosition()
{
	Vector2i temp = figure.get()->getPosition();
	temp *= PIXEL_SIZE;
	posInWindow = Vector2f(temp);
	swap(posInWindow.x, posInWindow.y);
}

void FigureView::setPosition(Vector2f pos)
{
	posInWindow = pos;
}

int FigureView::getFigureColorId()
{
	return figure.get()->getColourId();
}

shared_ptr<Figure> FigureView::getFigure()
{
	return figure;
}

void FigureView::setType(Figure::Type curType)
{
	posInTexture.x = (curType - 1)*PIXEL_SIZE;
}

FigureView::~FigureView()
{
	figure.reset();
	figure.reset();
}
