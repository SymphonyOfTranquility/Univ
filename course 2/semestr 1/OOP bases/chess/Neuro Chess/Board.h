#pragma once
#include "Figure.h"

#include <vector>

using namespace std;

struct TurnStruct;

class Board
{
public:
	enum MoveType
	{
		Common = 0,
		Eat,
		EnPassant,
		Castling,
		NewFigure,
	};
	enum EffectOnKing
	{
		None = 0,
		Check,
		Mate,
	};

	enum Colour
	{
		Black = 64,
		White = 128
	};
private:
	vector<shared_ptr<Figure> > figures[2];
	Tcell posFigures[BOARD_SIZE][BOARD_SIZE];
	bool gameType;

	static int moveQueenX[8], moveQueenY[8], moveRookX[4], moveRookY[4], moveBishopX[4], moveBishopY[4], moveKnightX[8], moveKnightY[8];

	
	pair<MoveType, EffectOnKing> prevFigureMove;
	int prevFigureNumber;
	Vector2i prevFigurePos;
	int eatEnPassantCastlingFigure;

	int endOfGame;

	union
	{
		Figure::Colour whoseTurn;
		int whoseTurnId;
	};
	
	bool compareTurn(const TurnStruct &a, const TurnStruct &b, int weight[]);
	void RestoreHeapTurn(vector<TurnStruct> &mas, int father, int count_tree, int weight[]);
	void myTurnSort(vector<TurnStruct> &mas, int weight[]);
	bool checkFieldUnderAttack(Vector2i pos, Colour colour);
	EffectOnKing checkEffectOnKing();
	bool empty(Vector2i pos);
	bool checkMakeMove(int figureNumber, Vector2i figurePos, MoveType curMove, int checkMate = -1);
	int getKingNumber(Colour colour);
public:
	Board();
	Board(shared_ptr<Board> curBoard);
	bool checkCanLeftThere(int figureNumber, Vector2i figurePos, int checkMate = -1);
	void checkMateDraw();
	bool outOfBoard(Vector2i pos);

	vector<shared_ptr<Figure> > getWhiteFigures();
	vector<shared_ptr<Figure> > getBlackFigures();

	bool getGameType();
	void setGameType(bool x);
	Figure::Colour getWhoseTurn();

	MoveType lastMoveType();
	int lastMoveFigure();
	Vector2i getSpecialFigurePos(); 
	int getSpecialFigure();
	int getPrevFigureNumber();
	pair<MoveType, EffectOnKing> getPrevFigureMove();
	Vector2i getPrevFigurePos();

	int isEndOfGame();
	///computer
	void changePositions(int movingFigure, Vector2i endPosBoard, Board::MoveType curMoveType, Figure::Type curType = Figure::Type::Pawn);
	void setWhoseTurn(Figure::Colour colour);

	vector<TurnStruct> makeMoves(Figure::Colour colour, int weight[]);
	void makeMoveComputer(TurnStruct turn);
	void unMakeMoveComputer(TurnStruct turn);

	Vector2i getKingPos(Figure::Colour colour);
	shared_ptr<Figure> getFigureInPos(int x, int y);

	~Board();
};


struct TurnStruct
{
	int number;
	Vector2i posToGo, posFromGo;
	bool moved;
	Figure::Colour colour;
	Board::MoveType moveType;
	Board::EffectOnKing effectOnKing;
	Figure::Type newFigure;

	int inflNumber;
	shared_ptr<Figure> influentFigure;
};