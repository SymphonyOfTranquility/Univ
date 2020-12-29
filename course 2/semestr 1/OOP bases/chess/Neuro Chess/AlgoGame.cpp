#include "AlgoGame.h"

int AlgoGame::weightPriority[6] = {(int)1e9 + 7, 900, 500, 350, 300, 100};
int AlgoGame::PositionPriorityKingStart[8][8] =
{
	{   0,   0,  -4, -10, -10,  -4,   0,   0},
	{  -4,  -4,  -8, -12, -12,  -8,  -4,  -4},
	{ -12, -16, -20, -20, -20, -20, -16, -12},
	{ -16, -20, -24, -24, -24, -24, -20, -16},
	{ -20, -24, -28, -28, -28, -28, -24, -20},
	{ -24, -28, -32, -32, -32, -32, -28, -24},
	{ -28, -32, -36, -36, -36, -36, -32, -28},
	{ -32, -36, -40, -40, -40, -40, -36, -32}
};
int AlgoGame::PositionPriorityKingEnd[8][8] =
{
	{  0,  6, 12, 18, 18, 12,  6,  0},
	{  6, 12, 18, 24, 24, 18, 12,  6},
	{ 12, 18, 24, 30, 30, 24, 18, 12},
	{ 18, 24, 30, 36, 36, 30, 24, 18},
	{ 18, 24, 30, 36, 36, 30, 24, 18},
	{ 12, 18, 24, 30, 30, 24, 18, 12},
	{  6, 12, 18, 24, 24, 18, 12,  6},
	{  0,  6, 12, 18, 18, 12,  6,  0}
};
int AlgoGame::PositionPriorityKnight[8][8] =
{
	{  0,  4,  8, 10, 10,  8,  4,  0},
	{  4,  8, 16, 20, 20, 16,  8,  4},
	{  8, 16, 24, 28, 28, 24, 16,  8},
	{ 10, 20, 28, 32, 32, 28, 20, 10},
	{ 10, 20, 28, 32, 32, 28, 20, 10},
	{  8, 16, 24, 28, 28, 24, 16,  8},
	{  4,  8, 16, 20, 20, 16,  8,  4},
	{  0,  4,  8, 10, 10,  8,  4,  0}
};
int AlgoGame::PositionPriorityBishop[8][8] =
{
	{ 14, 14, 14, 14, 14, 14, 14, 14},
	{ 14, 22, 18, 18, 18, 18, 22, 14},
	{ 14, 18, 22, 22, 22, 22, 18, 14},
	{ 14, 18, 22, 22, 22, 22, 18, 14},
	{ 14, 18, 22, 22, 22, 22, 18, 14},
	{ 14, 18, 22, 22, 22, 22, 18, 14},
	{ 14, 22, 18, 18, 18, 18, 22, 14},
	{ 14, 14, 14, 14, 14, 14, 14, 14}
};
int AlgoGame::PositionPriorityPawn[8][8] =
{
	{  0,  0,  0,  0,  0,  0,  0,  0},
	{  4,  4,  4,  0,  0,  4,  4,  4},
	{  6,  8,  2, 10, 10,  2,  8,  6},
	{  6,  8, 12, 16, 16, 12,  8,  6},
	{  8, 12, 16, 24, 24, 16, 12,  8},
	{ 12, 16, 24, 32, 32, 24, 16, 12},
	{ 12, 16, 24, 32, 32, 24, 16, 12},
	{  0,  0,  0,  0,  0,  0,  0,  0}
};
int AlgoGame::PositionPriorityPassedPawn[8] = { 0, 5, 10, 15, 20, 30, 140, 0 };

int AlgoGame::evaluateFunction(shared_ptr<Board>& curBoard)
{
	Figure::Colour idColour = curBoard.get()->getWhoseTurn();
	vector<shared_ptr<Figure> > allFigures;
	int ans = 0;
	for (int q = 0; q < 2; ++q) 
	{
		if (q == 0)
			allFigures = curBoard.get()->getBlackFigures();
		else
			allFigures = curBoard.get()->getWhiteFigures();
		
		for (int i = 0; i < allFigures.size(); ++i)
		{
			if (allFigures[i].get() != nullptr)
			{
				Vector2i tempPos = allFigures[i].get()->getPosition();
				Figure::Type idType = allFigures[i].get()->getType();
				int k = (allFigures[i].get()->getColour() == idColour ? 1 : -1);
				if (idType == Figure::Type::King)
				{
					if (idColour == Figure::Colour::Black)
					{
						if (current_time <= 30)
							ans += k * PositionPriorityKingStart[tempPos.x][tempPos.y];
						else
							ans += k * PositionPriorityKingEnd[tempPos.x][tempPos.y];
					}
					else
					{
						if (current_time <= 30)
							ans += k * PositionPriorityKingStart[BOARD_SIZE - tempPos.x - 1][tempPos.y];
						else
							ans += k * PositionPriorityKingEnd[tempPos.x][tempPos.y];
					}
				}
				else if (idType == Figure::Type::Queen)
				{
					ans += k * weightPriority[1];
					Vector2i kingPos = curBoard.get()->getKingPos(Figure::Colour(idColour % 128 + 64));
					ans += k * (8 - abs(kingPos.x - tempPos.x) - abs(kingPos.y - tempPos.y)) * 4;
				}
				else if (idType == Figure::Type::Rook)
				{
					ans += k * weightPriority[2];
					if (current_time > 45)
					{
						int y = (tempPos.y > 3 ? 8 - tempPos.y - 1 : tempPos.y);
						ans += k * y * 5;
					}
				}
				else if (idType == Figure::Type::Knight)
				{
					ans += k * weightPriority[3];
					ans += k * PositionPriorityKnight[tempPos.x][tempPos.y];
				}
				else if (idType == Figure::Type::Bishop)
				{
					ans += k * weightPriority[4];
					ans += k * PositionPriorityKnight[tempPos.x][tempPos.y];
				}
				else if (idType == Figure::Type::Pawn)
				{
					ans += k * weightPriority[5];
					int x = (allFigures[i].get()->getColour() == Figure::Colour::Black ? 1 : -1);
					shared_ptr<Figure> tempFigure = curBoard.get()->getFigureInPos(tempPos.x + x, tempPos.y);
					if (tempFigure != nullptr &&
						tempFigure.get()->getType() == idType &&
						tempFigure.get()->getColour() == allFigures[i].get()->getColour())
						ans += k * (-10);
					tempFigure = curBoard.get()->getFigureInPos(tempPos.x + x, tempPos.y + 1);
					if (tempFigure != nullptr &&
						tempFigure.get()->getType() == idType &&
						tempFigure.get()->getColour() == allFigures[i].get()->getColour())
						ans += k * 15;
					tempFigure = curBoard.get()->getFigureInPos(tempPos.x + x, tempPos.y - 1);
					if (tempFigure != nullptr &&
						tempFigure.get()->getType() == idType &&
						tempFigure.get()->getColour() == allFigures[i].get()->getColour())
						ans += k * 15;

					if (idColour == Figure::Colour::Black)
					{
						if (current_time <= 60)
							ans += k * PositionPriorityPawn[tempPos.x][tempPos.y];
						else
							ans += k * PositionPriorityPassedPawn[tempPos.y];
					}
					else
					{
						if (current_time <= 60)
							ans += k * PositionPriorityPawn[tempPos.x][BOARD_SIZE - tempPos.y - 1];
						else
							ans += k * PositionPriorityPassedPawn[BOARD_SIZE - tempPos.y - 1];
					}
				}
			}
		}
	}
	return ans;
}

int AlgoGame::AlphaBeta(int alpha, int beta, int depth, shared_ptr<Board> &curBoard)
{
	if (depth == 0)
		return evaluateFunction(curBoard);
	vector<TurnStruct> moveList = curBoard.get()->makeMoves(Figure::Colour(curBoard.get()->getWhoseTurn()), weightPriority);
	int res = -inf;
	for (int i = 0; i < (int)moveList.size(); ++i)
	{
		int endOfGame = -1;
		if (moveList[i].moveType == Board::Eat && moveList[i].effectOnKing == Board::Mate)
			endOfGame = 1;
		int curAns = -inf;
		if (endOfGame == 1)
			curAns = inf;
		else 
		{
			curBoard.get()->makeMoveComputer(moveList[i]);
			curAns = -AlphaBeta(-beta, -alpha, depth - 1, curBoard);
			curBoard.get()->unMakeMoveComputer(moveList[i]);
		}
		if (curAns > res)
			res = curAns;
		if (res > alpha) 
		{
			alpha = res;
			if (depth == 2)
				alphaBetaFigure = moveList[i];
		}
		if (alpha >= beta)
			return alpha;
	}
//	if ((int)moveList.size() == 0)
		return res;
}

AlgoGame::AlgoGame()
{
	endOfMove = false;
	moving = false;
	startTime = high_resolution_clock::now();
	timeLeft = false;
	current_time = 0;
}

bool AlgoGame::madeMove()
{
	return moving;
}

int AlgoGame::getMovingFigure()
{
	return alphaBetaFigure.number;
}

Board::MoveType AlgoGame::getMoveType()
{
	return alphaBetaFigure.moveType;
}

Figure::Type AlgoGame::getNewFigureType()
{
	return alphaBetaFigure.newFigure;
}

Vector2f AlgoGame::figureLawMove(Vector2f prevPos)
{
	high_resolution_clock::time_point current = high_resolution_clock::now();
	auto duration = duration_cast<chrono::microseconds>(current - startTime).count();
	double durInSec = double(duration) / 1000000.0;
	if (durInSec - timeLeft > 0.003)
	{
		Vector2f nextPos;
		if (lawLineB != 0) {
			nextPos.x = prevPos.x + float(lawStep);
			nextPos.y = float((-lawLineA * nextPos.x - lawLineC) / lawLineB);
		}
		else {
			nextPos.y = prevPos.y + float(lawStep);
			nextPos.x = float((-lawLineB * nextPos.y - lawLineC) / lawLineA);
		}


		if (abs(nextPos.x - endPositionInWindow.x) <= 3.0 &&
			abs(nextPos.y - endPositionInWindow.y) <= 3.0)
		{
			lawLineC = lawLineB = lawLineA = 0;
			moving = false;
			endOfMove = true;
		}
		timeLeft = durInSec;
		return nextPos;
	}
	return prevPos;
}

Vector2i AlgoGame::getEndPosBoard()
{
	return endPosOnBoard;
}

bool AlgoGame::getEndOfMove()
{
	return endOfMove;
}

void AlgoGame::setEndOfMove(bool val)
{
	endOfMove = val;
}



void AlgoGame::moveComputer(shared_ptr<Board> board)
{
	//AlphaBeta
	int x = AlphaBeta(-inf, inf, 2, board);
	++current_time;
	//vector<shared_ptr<Figure> >  allFigures = board.get()->getBlackFigures();
	moving = true;
	endOfMove = false;
	movingFigure = alphaBetaFigure.number;

	endPositionInWindow = Vector2f(alphaBetaFigure.posToGo * PIXEL_SIZE);
	endPosOnBoard = alphaBetaFigure.posToGo;
	swap(endPositionInWindow.x, endPositionInWindow.y);

	Vector2f vFrom = Vector2f(alphaBetaFigure.posFromGo);
	Vector2f vTo = Vector2f(alphaBetaFigure.posToGo);
	vFrom *= float(PIXEL_SIZE);
	vTo *= float(PIXEL_SIZE);
	swap(vTo.x, vTo.y);
	swap(vFrom.x, vFrom.y);
	lawLineA = (vTo.y - vFrom.y);
	lawLineB = -vTo.x + vFrom.x;
	lawLineC = (-vFrom.x*vTo.y + vFrom.y*vTo.x);
	double dist = sqrt((vFrom.x - vTo.x)*(vFrom.x - vTo.x) + (vFrom.y - vTo.y)*(vFrom.y - vTo.y)) / 3.0;
	if (vTo.x > vFrom.x)
		lawStep = abs(vTo.x - vFrom.x) / dist;
	else if (vTo.x < vFrom.x)
		lawStep = abs(vTo.x - vFrom.x) / (-dist);
	else if (vTo.y > vFrom.y)
		lawStep = abs(vTo.y - vFrom.y) / dist;
	else
		lawStep = abs(vTo.y - vFrom.y) / (-dist);
}

AlgoGame::~AlgoGame()
{
}
