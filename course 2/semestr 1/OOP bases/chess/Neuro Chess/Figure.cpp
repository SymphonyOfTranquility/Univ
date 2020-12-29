#include "Figure.h"



Figure::Figure(Type type, Colour colour, Vector2i pos) : type(type), colour(colour), pos(pos)
{
	moved = false;
}

Figure::Figure(int typeId, Colour colour, Vector2i pos) : typeId(typeId), colour(colour), pos(pos)
{
	moved = false;
}

Figure::Figure(shared_ptr<Figure> curFigure)
{
	typeId = curFigure.get()->getTypeId();
	colourId = curFigure.get()->getColourId();
	pos = curFigure.get()->getPosition();
	moved = curFigure.get()->isMoved();
}

Figure::Type Figure::getType()
{
	return type;
}

int Figure::getTypeId()
{
	return typeId;
}

Figure::Colour Figure::getColour()
{
	return colour;
}

int Figure::getColourId()
{
	return colourId;
}

void Figure::setPosition(Vector2i setPos)
{
	pos = setPos;
}

Vector2i Figure::getPosition()
{
	return pos;
}

bool Figure::isMoved()
{
	return moved;
}

void Figure::setMoved()
{
	moved = true;
}

void Figure::setDeMoved()
{
	moved = false;
}

void Figure::setType(Figure::Type curType)
{
	type = curType;
}


Figure::~Figure()
{
}
