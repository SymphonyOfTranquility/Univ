#pragma once
#include "Board.h"
#include "FigureView.h"
#include <chrono>
#include <iostream>
#include <fstream>
//#include 

using namespace std;
using namespace sf;
using namespace std::chrono;

const int inf = 10000;

class AlgoGame
{

	bool endOfMove;
	Vector2f endPositionInWindow;
	Vector2i endPosOnBoard;

	bool moving;
	int movingFigure;
	Board::MoveType moveTypeMovingFigure;
	Figure::Type newFigureType;

	double lawLineA, lawLineB, lawLineC, lawStep;

	high_resolution_clock::time_point startTime;
	double timeLeft;

	TurnStruct alphaBetaFigure;

	string text;
	int current_time;
	static int PositionPriorityKingStart[8][8], PositionPriorityKingEnd[8][8];
	static int PositionPriorityKnight[8][8];
	static int PositionPriorityBishop[8][8];
	static int PositionPriorityPawn[8][8];
	static int PositionPriorityPassedPawn[8];
	static int weightPriority[6];

	int evaluateFunction(shared_ptr<Board> &curBoard);
	int AlphaBeta(int alpha, int beta, int depth, shared_ptr<Board> &curBoard);
public:
	AlgoGame();
	bool madeMove();
	int getMovingFigure();
	Board::MoveType getMoveType();
	Figure::Type getNewFigureType();
	Vector2f figureLawMove(Vector2f prevPos);
	Vector2i getEndPosBoard();
	bool getEndOfMove();
	void setEndOfMove(bool val);
	void moveComputer(shared_ptr<Board> board);
	~AlgoGame();
};

