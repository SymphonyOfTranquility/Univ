#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

const int BOARD_SIZE = 8;

struct Tcell
{
	int posInVector;
	bool isUnderAttack;
};

class Figure
{
public:
	enum Type
	{
		King = 1,
		Queen,
		Rook,
		Knight,
		Bishop,
		Pawn
	};
	enum Colour
	{
		Black = 64,
		White = 128
	};
	Figure(Type type, Colour colour, Vector2i pos);
	Figure(int typeId, Colour colour, Vector2i pos);
	Figure(shared_ptr<Figure> curFigure);
	Figure::Type getType();
	int getTypeId();
	Figure::Colour getColour();
	int getColourId();
	void setPosition(Vector2i setPos);
	Vector2i getPosition();
	bool isMoved();
	void setMoved();
	void setDeMoved();
	void setType(Figure::Type curType);
	~Figure();

private:
	union
	{
		Type type;
		int typeId;
	};
	union
	{
		Colour colour;
		int colourId;
	};
	bool moved;
	Vector2i pos;
};

