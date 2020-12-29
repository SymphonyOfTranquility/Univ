#pragma once
#include "AlgoGame.h"
#include "FigureView.h"
#include "Board.h"

const Vector2i offSet = Vector2i(25, 25);

class BoardView
{
	shared_ptr<Board> board;
	shared_ptr<AlgoGame> algoGame;
	shared_ptr<RenderTexture> renderBoard;
	shared_ptr<Sprite> boardSprite;
	shared_ptr<Texture> figureTexture;
	shared_ptr<Sprite> figureSprite;

	vector<shared_ptr<FigureView> > viewOfFigures[2];
	int isUnderMouse, underMouseColour;


	string newWindow;
	bool attention;
	string textOfEnd;

public:
	BoardView();
	void draw(shared_ptr<RenderWindow> &window);
	void pollEvent(Event event, shared_ptr<RenderWindow> &window);
	void withoutEvent();

	bool checkMousePressedFigure(Vector2i mousePos);
	void checkMouseReleasedFigure();
	bool checkMouseOutOfBoard(Vector2i mousePos);

	bool getGameType();
	void setGameType(bool typeGame);
	void endOfGame();
	string getTextOfEnd();

	string needNewWindow();
	Figure::Colour getWhoseTurn();

	void setFigureType(Figure::Type type);
	~BoardView();
};

