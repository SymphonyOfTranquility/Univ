#include "Board.h"

int Board::moveQueenX[8] = {  1,1,1, 0,0,-1,-1,-1 };
int Board::moveQueenY[8] = { -1,0,1,-1,1,-1, 0, 1 };
int Board::moveRookX[4] = { 0,1,-1, 0 };
int Board::moveRookY[4] = { 1,0, 0,-1 };
int Board::moveBishopX[4] = {  1, 1,-1,-1 };
int Board::moveBishopY[4] = { -1, 1,-1, 1 };
int Board::moveKnightX[8] = { -2, -2, -1, -1,  1, 1,  2, 2 };
int Board::moveKnightY[8] = { -1,  1, -2,  2, -2, 2, -1, 1 };


bool Board::compareTurn(const TurnStruct & a, const TurnStruct & b, int weight[])
{
	if (a.moveType < b.moveType)
		return true;
	else if (a.moveType > b.moveType)
		return false;
	else if (a.moveType == Eat)
	{
		int x1 = weight[figures[a.colour/White][a.number].get()->getTypeId() - 1],
			y1 = weight[figures[b.colour/White][b.number].get()->getTypeId() - 1],
			x2 = weight[a.influentFigure->getTypeId() - 1],
			y2 = weight[b.influentFigure->getTypeId() - 1];
		if (x1 - x2 > y1 - y2)
			return true;
		else
			return false;
	}
	else if (figures[a.colour/White][a.number].get()->getTypeId() > figures[b.colour/White][b.number].get()->getTypeId())
		return true;
	else
		return false;

}

void Board::RestoreHeapTurn(vector<TurnStruct> &mas, int father, int count_tree, int weight[])
{
	int maxson;
	while (father <= count_tree / 2)
	{
		if (father * 2 == count_tree)
			maxson = father * 2;
		else if (compareTurn(mas[father * 2], mas[father * 2 - 1], weight))
			maxson = father * 2 + 1;
		else
			maxson = father * 2;
		if (compareTurn(mas[maxson - 1], mas[father - 1], weight))
		{
			swap(mas[maxson - 1], mas[father - 1]);
			father = maxson;
		}
		else
			father = count_tree;
	}
}

void Board::myTurnSort(vector<TurnStruct> &mas, int weight[])
{
	for (int i = mas.size() / 2; i > 0; --i)
		RestoreHeapTurn(mas, i, mas.size(), weight);
	for (int i = mas.size(); i > 0; --i)
	{
		swap(mas[0], mas[i - 1]);
		RestoreHeapTurn(mas, 1, i - 1, weight);
	}
}

bool Board::checkFieldUnderAttack(Vector2i pos, Colour colour)
{
	for (int i = 0; i < BOARD_SIZE/2; ++i)
	{
		Vector2i cur = pos;
		cur.x += moveRookX[i];
		cur.y += moveRookY[i];
		while (!outOfBoard(cur))
		{
			if (!empty(cur))
			{
				int figure = posFigures[cur.x][cur.y].posInVector;
				if (figure / White == colour / White)
				{
					int number;
					if (figure / White == 1)
						number = figure - White;
					else
						number = figure - Black;
					if (figures[colour/White][number].get()->getType() == Figure::Type::Queen ||
						abs(cur.x - pos.x)+abs(cur.y-pos.y) == 1  && figures[colour/White][number].get()->getType() == Figure::Type::King ||
						figures[colour/White][number].get()->getType() == Figure::Type::Rook)
						return true;
				}
				break;
			}				
			cur.x += moveRookX[i];
			cur.y += moveRookY[i];
		}
	}
	for (int i = 0; i < BOARD_SIZE / 2; ++i)
	{
		Vector2i cur = pos;
		cur.x += moveBishopX[i];
		cur.y += moveBishopY[i];
		while (!outOfBoard(cur))
		{
			if (!empty(cur))
			{
				int figure = posFigures[cur.x][cur.y].posInVector;
				if (figure / White == colour / White)
				{
					int number;
					if (figure / White == 1)
						number = figure - White;
					else
						number = figure - Black;
					if ((cur.x - pos.x == -1 && colour == Black || cur.x - pos.x == 1 && colour == White) &&
						figures[colour / White][number].get()->getType() == Figure::Type::Pawn)
							return true;
					if (figures[colour / White][number].get()->getType() == Figure::Type::Queen ||
						abs(cur.x - pos.x) == 1 && figures[colour / White][number].get()->getType() == Figure::Type::King ||
						figures[colour / White][number].get()->getType() == Figure::Type::Bishop)
						return true;
				}
				break;
			}
			cur.x += moveBishopX[i];
			cur.y += moveBishopY[i];
		}
	}
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		Vector2i cur = pos;
		cur.x += moveKnightX[i];
		cur.y += moveKnightY[i];
		if (!outOfBoard(cur) && !empty(cur))
		{
			int figure = posFigures[cur.x][cur.y].posInVector;
			if (figure / White == colour / White)
			{
				int number;
				if (figure / White == 1)
					number = figure - White;
				else
					number = figure - Black;
				if (figures[colour / White][number].get()->getType() == Figure::Type::Knight)
					return true;
			}
		}
	}
	return false;
}

Board::EffectOnKing Board::checkEffectOnKing()
{
	int king = getKingNumber(Colour(whoseTurn));
	if (checkFieldUnderAttack(figures[whoseTurn / White][king].get()->getPosition(), (Colour)(whoseTurnId%White + Black)))
		return Check;
	else
		return None;
}

bool Board::empty(Vector2i pos)
{
	return (posFigures[pos.x][pos.y].posInVector == -1);
}

bool Board::checkMakeMove(int figureNumber, Vector2i figurePos, MoveType curMove, int checkMate)
{
	Vector2i tempPrevPos = figures[whoseTurn / White][figureNumber].get()->getPosition();
	if (curMove == Common)
	{
		posFigures[figurePos.x][figurePos.y].posInVector = posFigures[tempPrevPos.x][tempPrevPos.y].posInVector;
		posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = -1;
		figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
		if (checkEffectOnKing() == None)
		{
			if (checkMate != -1)
			{
				posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
				posFigures[figurePos.x][figurePos.y].posInVector = -1;
				figures[whoseTurn / White][figureNumber].get()->setPosition(tempPrevPos);
				return true;
			}
			figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
			figures[whoseTurn / White][figureNumber].get()->setMoved();
			prevFigureNumber = figureNumber;
			prevFigurePos = tempPrevPos;
			eatEnPassantCastlingFigure = -1;
			prevFigureMove.first = Common;
			prevFigureMove.second = None;
			whoseTurnId = whoseTurn % White + Black;
			return true;
		}
		posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
		posFigures[figurePos.x][figurePos.y].posInVector = -1;
		figures[whoseTurn / White][figureNumber].get()->setPosition(tempPrevPos);
	}
	else if (curMove == Eat)
	{
		int eatenFigure = posFigures[figurePos.x][figurePos.y].posInVector; 
		posFigures[figurePos.x][figurePos.y].posInVector = posFigures[tempPrevPos.x][tempPrevPos.y].posInVector;
		posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = -1;
		figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
		figures[(whoseTurn%White + Black) / White][(eatenFigure / White == 0 ? eatenFigure - Black : eatenFigure - White)].get()->setPosition(Vector2i(-1,-1));
		if (checkEffectOnKing() == None)
		{
			if (checkMate != -1)
			{
				posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
				posFigures[figurePos.x][figurePos.y].posInVector = eatenFigure;
				figures[whoseTurn / White][figureNumber].get()->setPosition(tempPrevPos);
				figures[(whoseTurn%White + Black) / White][(eatenFigure / White == 0 ? eatenFigure - Black : eatenFigure - White)].get()->
					setPosition(figurePos);
				return true;
			}
			figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
			figures[whoseTurn / White][figureNumber].get()->setMoved();
			int number = (eatenFigure / White == 0 ? eatenFigure - Black : eatenFigure - White);
			figures[eatenFigure / White][number].reset();
			prevFigureNumber = figureNumber;
			prevFigurePos = tempPrevPos;
			eatEnPassantCastlingFigure = eatenFigure;
			prevFigureMove.first = Eat;
			prevFigureMove.second = None;
			whoseTurnId = whoseTurn % White + Black;
			return true;
		}
		posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
		posFigures[figurePos.x][figurePos.y].posInVector = eatenFigure;
		figures[whoseTurn / White][figureNumber].get()->setPosition(tempPrevPos);
		figures[(whoseTurn%White + Black) / White][(eatenFigure / White == 0 ? eatenFigure - Black : eatenFigure - White)].get()->
			setPosition(figurePos);
	}
	else if (curMove == EnPassant)
	{
		Vector2i curPosPrevFigure = figures[(int)(!bool(whoseTurn / White))][prevFigureNumber].get()->getPosition();
		Vector2i tempSubForPrev = curPosPrevFigure - prevFigurePos;
		if (abs(tempSubForPrev.x) == 2 && tempSubForPrev.y == 0)
		{
			if (curPosPrevFigure.y == figurePos.y && curPosPrevFigure.x == tempPrevPos.x)
			{
				int enPassantFigure = posFigures[curPosPrevFigure.x][curPosPrevFigure.y].posInVector;
				posFigures[curPosPrevFigure.x][curPosPrevFigure.y].posInVector = -1;
				posFigures[figurePos.x][figurePos.y].posInVector = posFigures[tempPrevPos.x][tempPrevPos.y].posInVector;
				posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = -1;
				figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
				figures[(whoseTurn%White + Black) / White][(enPassantFigure / White == 0 ? enPassantFigure - Black : enPassantFigure - White)].get()->setPosition(Vector2i(-1, -1));
				if (checkEffectOnKing() == None)
				{
					if (checkMate != -1)
					{
						posFigures[curPosPrevFigure.x][curPosPrevFigure.y].posInVector = enPassantFigure;
						posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
						posFigures[figurePos.x][figurePos.y].posInVector = -1;
						figures[whoseTurn / White][figureNumber].get()->setPosition(tempPrevPos);
						figures[(whoseTurn%White + Black) / White][(enPassantFigure / White == 0 ? enPassantFigure - Black : enPassantFigure - White)].get()->
							setPosition(curPosPrevFigure);
						return true;
					}
					figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
					figures[whoseTurn / White][figureNumber].get()->setMoved();
					int number = (enPassantFigure / White == 0 ? enPassantFigure - Black : enPassantFigure - White);
					figures[enPassantFigure / White][number].reset();
					prevFigureNumber = figureNumber;
					prevFigurePos = tempPrevPos;
					eatEnPassantCastlingFigure = enPassantFigure;
					prevFigureMove.first = EnPassant;
					prevFigureMove.second = None;
					whoseTurnId = whoseTurn % White + Black;
					return true;
				}
				posFigures[curPosPrevFigure.x][curPosPrevFigure.y].posInVector = enPassantFigure;
				posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
				posFigures[figurePos.x][figurePos.y].posInVector = -1; 
				figures[whoseTurn / White][figureNumber].get()->setPosition(tempPrevPos);
				figures[(whoseTurn%White + Black) / White][(enPassantFigure / White == 0 ? enPassantFigure - Black : enPassantFigure - White)].get()->
					setPosition(curPosPrevFigure);
			}
		}
	}
	else if (curMove == Castling)
	{
		int movedRook,step;
		if (figurePos.y > tempPrevPos.y) 
		{
			movedRook = posFigures[tempPrevPos.x][BOARD_SIZE - 1].posInVector;
			step = 1;
		}
		else
		{
			movedRook = posFigures[tempPrevPos.x][0].posInVector;
			step = -1;
		}
		int number = (movedRook / White ? movedRook - White : movedRook - Black);
		if (movedRook != -1 && movedRook / White == whoseTurn / White &&
			figures[movedRook / White][number].get()->getType() == Figure::Type::Rook &&
			!figures[movedRook / White][number].get()->isMoved())
		{
			Vector2i rookPos = figures[movedRook / White][number].get()->getPosition();
			for (int i = tempPrevPos.y; i != rookPos.y + step; i += step)
			{
				if (i != tempPrevPos.y && i != rookPos.y && !empty(Vector2i(tempPrevPos.x, i)))
					return false;
				if (checkFieldUnderAttack(Vector2i(tempPrevPos.x, i), Colour(whoseTurn%White+Black)))
					return false;
			}
			if (checkMate != -1)
				return true;
			posFigures[tempPrevPos.x][tempPrevPos.y+step].posInVector = posFigures[rookPos.x][rookPos.y].posInVector;
			posFigures[figurePos.x][figurePos.y].posInVector = posFigures[tempPrevPos.x][tempPrevPos.y].posInVector;
			posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[rookPos.x][rookPos.y].posInVector = -1;
			figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
			figures[whoseTurn / White][number].get()->setPosition(Vector2i(tempPrevPos.x,tempPrevPos.y+step));
			prevFigureNumber = figureNumber;
			prevFigurePos = tempPrevPos;
			eatEnPassantCastlingFigure = movedRook;
			prevFigureMove.first = Castling;
			prevFigureMove.second = None;
			whoseTurnId = whoseTurn % White + Black;
			return true;
		}
	}
	else if (curMove == NewFigure)
	{
		Vector2i tempSub = figurePos - tempPrevPos;
		if (tempSub.y == 0)
		{
			posFigures[figurePos.x][figurePos.y].posInVector = posFigures[tempPrevPos.x][tempPrevPos.y].posInVector;
			posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = -1;
			if (checkEffectOnKing() == None)
			{
				if (checkMate != -1)
				{
					posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
					posFigures[figurePos.x][figurePos.y].posInVector = -1;					
					return true;
				}
				figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
				figures[whoseTurn / White][figureNumber].get()->setMoved();
				prevFigureNumber = figureNumber;
				prevFigurePos = tempPrevPos;
				eatEnPassantCastlingFigure = -1;
				prevFigureMove.first = NewFigure;
				prevFigureMove.second = None;
				whoseTurnId = whoseTurn % White + Black;
				return true;
			}
			posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
			posFigures[figurePos.x][figurePos.y].posInVector = -1;
		}
		else
		{
			int eatenFigure = posFigures[figurePos.x][figurePos.y].posInVector;
			posFigures[figurePos.x][figurePos.y].posInVector = posFigures[tempPrevPos.x][tempPrevPos.y].posInVector;
			posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = -1;
			if (checkEffectOnKing() == None)
			{
				if (checkMate != -1)
				{
					posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
					posFigures[figurePos.x][figurePos.y].posInVector = eatenFigure;
					return true;
				}
				figures[whoseTurn / White][figureNumber].get()->setPosition(figurePos);
				figures[whoseTurn / White][figureNumber].get()->setMoved();
				int number = (eatenFigure / White == 0 ? eatenFigure - Black : eatenFigure - White);
				figures[eatenFigure / White][number].reset();
				prevFigureNumber = figureNumber;
				prevFigurePos = tempPrevPos;
				eatEnPassantCastlingFigure = eatenFigure;
				prevFigureMove.first = NewFigure;
				prevFigureMove.second = None;
				whoseTurnId = whoseTurn % White + Black;
				return true;
			}
			posFigures[tempPrevPos.x][tempPrevPos.y].posInVector = posFigures[figurePos.x][figurePos.y].posInVector;
			posFigures[figurePos.x][figurePos.y].posInVector = eatenFigure;
		}

	}
	return false;
}

int Board::getKingNumber(Colour colour)
{
	int king;
	for (int i = (int)figures[colour / White].size() - 1; i >= 0; --i)
	{
		if (figures[colour / White][i] != nullptr && figures[colour / White][i].get()->getType() == Figure::Type::King) 
		{
			king = i;
			break;
		}
	}
	return king;
}

Board::Board()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j) {
			posFigures[i][j].isUnderAttack = false;
			posFigures[i][j].posInVector = -1;
		}
	shared_ptr<Figure> tempFigure;
	Vector2i pos;
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		pos.x = 1; pos.y = i;
		posFigures[pos.x][pos.y].posInVector = (int)figures[0].size() + Figure::Colour::Black;
		tempFigure = shared_ptr<Figure>(new Figure(Figure::Type::Pawn, Figure::Colour::Black, pos));
		figures[0].push_back(tempFigure);

		pos.x = BOARD_SIZE - 2;
		posFigures[pos.x][pos.y].posInVector = (int)figures[1].size() + Figure::Colour::White;
		tempFigure = shared_ptr<Figure>(new Figure(Figure::Type::Pawn, Figure::Colour::White, pos));
		figures[1].push_back(tempFigure);
	}

	for (int i = 3; i <= 5; ++i)
	{
		pos.x = 0; pos.y = i - 3;
		posFigures[pos.x][pos.y].posInVector = (int)figures[0].size() + Figure::Colour::Black;
		tempFigure = shared_ptr<Figure>(new Figure(i, Figure::Colour::Black, pos));
		figures[0].push_back(tempFigure);

		pos.x = BOARD_SIZE - 1;
		posFigures[pos.x][pos.y].posInVector = (int)figures[1].size() + Figure::Colour::White;
		tempFigure = shared_ptr<Figure>(new Figure(i, Figure::Colour::White, pos));
		figures[1].push_back(tempFigure);


		pos.x = 0; pos.y = BOARD_SIZE - i + 2;
		posFigures[pos.x][pos.y].posInVector = (int)figures[0].size() + Figure::Colour::Black;
		tempFigure = shared_ptr<Figure>(new Figure(i, Figure::Colour::Black, pos));
		figures[0].push_back(tempFigure);

		pos.x = BOARD_SIZE - 1;
		posFigures[pos.x][pos.y].posInVector = (int)figures[1].size() + Figure::Colour::White;
		tempFigure = shared_ptr<Figure>(new Figure(i, Figure::Colour::White, pos));
		figures[1].push_back(tempFigure);
	}

	for (int i = 2; i >= 1; --i)
	{
		pos.x = 0; pos.y = BOARD_SIZE - i - 3;
		posFigures[pos.x][pos.y].posInVector = (int)figures[0].size() + Figure::Colour::Black;
		tempFigure = shared_ptr<Figure>(new Figure(i, Figure::Colour::Black, pos));
		figures[0].push_back(tempFigure);

		pos.x = BOARD_SIZE - 1;
		posFigures[pos.x][pos.y].posInVector = (int)figures[1].size() + Figure::Colour::White;
		tempFigure = shared_ptr<Figure>(new Figure(i, Figure::Colour::White, pos));
		figures[1].push_back(tempFigure);
	}

	gameType = 1;
	whoseTurn = Figure::Colour::White;
	prevFigureNumber = -1;

	endOfGame = 0;
}

Board::Board(shared_ptr<Board> copy)
{
	vector<shared_ptr<Figure> > tempFigures = copy.get()->getBlackFigures();
	for (int i = 0; i < tempFigures.size(); ++i)
	{
		shared_ptr<Figure> tempFigure;
		if (tempFigures[i] != nullptr)
			tempFigure = shared_ptr<Figure>(new Figure
			(tempFigures[i].get()->getType(), tempFigures[i].get()->getColour(), tempFigures[i].get()->getPosition()));
		else
			tempFigure.reset();
		figures[0].push_back(tempFigure);
	}
	tempFigures = copy.get()->getWhiteFigures();
	for (int i = 0; i < tempFigures.size(); ++i)
	{
		shared_ptr<Figure> tempFigure;
		if (tempFigures[i] != nullptr)
			tempFigure = shared_ptr<Figure>(new Figure
			(tempFigures[i].get()->getType(), tempFigures[i].get()->getColour(), tempFigures[i].get()->getPosition()));
		else
			tempFigure.reset();
		figures[1].push_back(tempFigure);
	}

	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			posFigures[i][j].posInVector = -1;
		}
	for (int j = 0;j < 2; ++j)
		for (int i = 0; i < figures[j].size(); ++i)
		{
			if (figures[j][i] != nullptr)
			{
				Vector2i tempPos = figures[j][i].get()->getPosition();
				posFigures[tempPos.x][tempPos.y].posInVector = i + (j+1)*Black;
			}
		}

	prevFigureNumber = copy.get()->getPrevFigureNumber();
	prevFigureMove = copy.get()->getPrevFigureMove();
	prevFigurePos = copy.get()->getPrevFigurePos();
	eatEnPassantCastlingFigure = copy.get()->getSpecialFigure();

	whoseTurn = Figure::Colour::Black;
	gameType = true;
}

bool Board::checkCanLeftThere(int figureNumber, Vector2i figurePos, int checkMate)
{
	bool ok = false;
	if (empty(figurePos) || posFigures[figurePos.x][figurePos.y].posInVector/White != whoseTurn/White)
	{
		Figure::Type curType = figures[whoseTurn/White][figureNumber].get()->getType();
		MoveType currentMove;
		Vector2i cur = figures[whoseTurn / White][figureNumber].get()->getPosition();
		if (cur == figurePos)
			return false;
		switch (curType)
		{
			case Figure::Type::King:
			{
				for (int i = 0; i < BOARD_SIZE; ++i)
				{
					cur.x += moveQueenX[i];
					cur.y += moveQueenY[i];
					if (cur == figurePos)
					{
						ok = true;
						if (empty(figurePos))
							currentMove = Common;
						else
							currentMove = Eat;
						break;
					}
					cur.x -= moveQueenX[i];
					cur.y -= moveQueenY[i];
				}
				if (!ok)
				{
					if (!figures[whoseTurn / White][figureNumber].get()->isMoved())
					{
						if (cur.x == figurePos.x && abs(cur.y - figurePos.y) == 2)
						{
							ok = true;
							currentMove = Castling;
						}
					}
				}
			}break;
			case Figure::Type::Queen:
			{
				for (int i = 0; i < BOARD_SIZE; ++i)
				{
					cur = figures[whoseTurn / White][figureNumber].get()->getPosition();
					cur.x += moveQueenX[i];
					cur.y += moveQueenY[i];
					while (cur.x >= 0 && cur.x < BOARD_SIZE && cur.y >= 0 && cur.y < BOARD_SIZE) 
					{
						if (cur == figurePos)
						{
							ok = true;
							if (empty(figurePos))
								currentMove = Common;
							else
								currentMove = Eat;
							break;
						}
						if (!empty(cur))
							break;
						cur.x += moveQueenX[i];
						cur.y += moveQueenY[i];
					}
				}
			}break;
			case Figure::Type::Rook:
			{
				for (int i = 0; i < BOARD_SIZE/2; ++i)
				{
					cur = figures[whoseTurn / White][figureNumber].get()->getPosition();
					cur.x += moveRookX[i];
					cur.y += moveRookY[i];
					while (cur.x >= 0 && cur.x < BOARD_SIZE && cur.y >= 0 && cur.y < BOARD_SIZE)
					{
						if (cur == figurePos)
						{
							ok = true;
							if (empty(figurePos))
								currentMove = Common;
							else
								currentMove = Eat;
							break;
						}
						if (!empty(cur))
							break;
						cur.x += moveRookX[i];
						cur.y += moveRookY[i];
					}
				}
			}break;
			case Figure::Type::Knight:
			{
				for (int i = 0; i < BOARD_SIZE; ++i)
				{
					cur.x += moveKnightX[i];
					cur.y += moveKnightY[i];
					if (cur == figurePos)
					{
						ok = true;
						if (empty(figurePos))
							currentMove = Common;
						else
							currentMove = Eat;
						break;
					}
					cur.x -= moveKnightX[i];
					cur.y -= moveKnightY[i];
				}			
			}break;
			case Figure::Type::Bishop:
			{
				for (int i = 0; i < BOARD_SIZE / 2; ++i)
				{
					cur = figures[whoseTurn / White][figureNumber].get()->getPosition();
					cur.x += moveBishopX[i];
					cur.y += moveBishopY[i];
					while (cur.x >= 0 && cur.x < BOARD_SIZE && cur.y >= 0 && cur.y < BOARD_SIZE)
					{
						if (cur == figurePos)
						{
							ok = true;
							if (empty(figurePos))
								currentMove = Common;
							else
								currentMove = Eat;
							break;
						}
						if (!empty(cur))
							break;
						cur.x += moveBishopX[i];
						cur.y += moveBishopY[i];
					}
				}

			}break;
			case Figure::Type::Pawn:
			{
				Vector2i temp = figurePos - cur;
				if (abs(temp.x) + abs(temp.y) == 1 && abs(temp.x) == 1)
				{
					if (empty(figurePos))
					{
						if (whoseTurn == Black && temp.x > 0 ||
							whoseTurn == White && temp.x < 0)
						{
							ok = true;
							if (figurePos.x == BOARD_SIZE - 1 || figurePos.x == 0)
								currentMove = NewFigure;
							else
								currentMove = Common;
						}
					}
				}
				else if (abs(temp.x) + abs(temp.y) == 2 && abs(temp.x) == 2 && (cur.x == 1 || cur.x == BOARD_SIZE-2))
				{
					Vector2i tempMid = (figurePos + cur) / 2;
					if (empty(figurePos) && empty(tempMid))
					{
						if (whoseTurn == Black && temp.x > 0 ||
							whoseTurn == White && temp.x < 0)
						{
							ok = true;
							currentMove = Common;
						}
					}
				}
				else if (abs(temp.x) == 1 && abs(temp.y) == 1)
				{
					if (!empty(figurePos))
					{ 
						if (whoseTurn == Black && temp.x > 0 ||
							whoseTurn == White && temp.x < 0)
						{
							ok = true;
							if (figurePos.x == BOARD_SIZE - 1 || figurePos.x == 0)
								currentMove = NewFigure;
							else
								currentMove = Eat;
						}
					}
					else
					{
						if (whoseTurn == Black && temp.x > 0 && cur.x == BOARD_SIZE / 2 ||
							whoseTurn == White && temp.x < 0 && cur.x == BOARD_SIZE / 2 - 1)
						{
							if (prevFigureNumber != -1 &&
								figures[(whoseTurn / White + 1) % 2][prevFigureNumber].get()->getType() == Figure::Type::Pawn &&
								prevFigureMove.first == Common)
							{
								ok = true;
								currentMove = EnPassant;
							}
						}
					}
				}				
			}break;
		}
		if (ok)
			return checkMakeMove(figureNumber, figurePos, currentMove, checkMate);
	}
	return false;
}

void Board::checkMateDraw()
{
	EffectOnKing effect = checkEffectOnKing();
	int counter = 0;
	for (int i = 0; i < figures[whoseTurn/White].size(); ++i)
	{
		if (figures[whoseTurn / White][i] != nullptr)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
				for (int k = 0; k < BOARD_SIZE; ++k)
				{
					if (figures[whoseTurn / White][i].get()->getPosition() != Vector2i(j, k))
					{
						if (this->checkCanLeftThere(i, Vector2i(j, k), 1))
						{
							++counter;
							break;
						}
					}
				}
			if (counter > 0)
				break;
		}
	}
	if (counter > 0)
		endOfGame = 0;
	else if (counter == 0)
	{
		if (effect != None)
			endOfGame = 1;
		else
			endOfGame = -1;
	}
}

bool Board::outOfBoard(Vector2i pos)
{
	return !(0 <= pos.x && pos.x < BOARD_SIZE && 0 <= pos.y && pos.y < BOARD_SIZE);
}

vector<TurnStruct> Board::makeMoves(Figure::Colour colour, int weight[])
{
	vector<TurnStruct> allMoves;
	TurnStruct curTurn;
	for (int i = 0; i < figures[colour / White].size(); ++i)
	{
		if (figures[colour / White][i] != nullptr)
		{
			Figure::Type curType = figures[colour / White][i].get()->getType();
			Vector2i cur = figures[colour / White][i].get()->getPosition();
			curTurn.moved = figures[colour / White][i].get()->isMoved();
			curTurn.colour = colour;
			curTurn.posFromGo = cur;
			curTurn.number = i;
			switch (curType)
			{
			case Figure::Type::King:
			{
				for (int j = 0; j < BOARD_SIZE; ++j)
				{
					cur.x += moveQueenX[j];
					cur.y += moveQueenY[j];
					if (!outOfBoard(cur) && empty(cur))
					{
						curTurn.moveType = Common;
						curTurn.effectOnKing = None;
						curTurn.posToGo = cur;
						curTurn.inflNumber = -1;
						curTurn.influentFigure = nullptr;
						allMoves.push_back(curTurn);
					}
					else if (!outOfBoard(cur))
					{
						int tempColour = posFigures[cur.x][cur.y].posInVector / White;
						if (tempColour != colour / White)
						{
							int number = posFigures[cur.x][cur.y].posInVector -
								(tempColour + 1)*Black;
							curTurn.moveType = Eat;
							curTurn.posToGo = cur;
							curTurn.inflNumber = number;
							curTurn.influentFigure = shared_ptr<Figure>(new Figure(figures[tempColour][number]));
							if (figures[tempColour][number].get()->getType() == Figure::Type::King)
								curTurn.effectOnKing = Mate;
							else
								curTurn.effectOnKing = None;
							allMoves.push_back(curTurn);
						}
					}
					cur.x -= moveQueenX[j];
					cur.y -= moveQueenY[j];
				}
				if (!figures[colour / White][i].get()->isMoved())
				{
					cur = figures[colour / White][i].get()->getPosition();
					int movedRook = posFigures[cur.x][BOARD_SIZE - 1].posInVector;
					int rookNumber = (movedRook / White ? movedRook - White : movedRook - Black);
					if (movedRook != -1 && movedRook / White == colour / White &&
						figures[movedRook / White][rookNumber].get()->getType() == Figure::Type::Rook &&
						!figures[movedRook / White][rookNumber].get()->isMoved())
					{
						cur.y += 2;
						bool ok = true;
						for (int j = cur.y - 2; j < BOARD_SIZE; ++j)
						{
							if (j != cur.y - 2 && j != BOARD_SIZE - 1 && !empty(Vector2i(cur.x, j)))
							{
								ok = false;
								break;
							}
							if (checkFieldUnderAttack(Vector2i(cur.x, j), Colour((int)colour%White + Black)))
							{
								ok = false;
								break;
							}
						}
						if (ok)
						{
							curTurn.moveType = Castling;
							curTurn.effectOnKing = None;
							curTurn.posToGo = cur; curTurn.inflNumber = rookNumber;
							curTurn.influentFigure = shared_ptr<Figure>(new Figure(figures[colour / White][rookNumber]));
							allMoves.push_back(curTurn);
						}
					}
					movedRook = posFigures[cur.x][0].posInVector;
					rookNumber = (movedRook / White ? movedRook - White : movedRook - Black);
					if (movedRook != -1 && movedRook / White == colour / White &&
						figures[movedRook / White][rookNumber].get()->getType() == Figure::Type::Rook &&
						!figures[movedRook / White][rookNumber].get()->isMoved())
					{
						cur.y -= 2;
						bool ok = true;
						for (int j = cur.y + 2; j >= 0; --j)
						{
							if (j != cur.y + 2 && j != 0 && !empty(Vector2i(cur.x, j)))
							{
								ok = false;
								break;
							}
							if (checkFieldUnderAttack(Vector2i(cur.x, j), Colour((int)colour%White + Black)))
							{
								ok = false;
								break;
							}
						}
						if (ok)
						{
							curTurn.moveType = Castling;
							curTurn.effectOnKing = None;
							curTurn.posToGo = cur; curTurn.inflNumber = rookNumber;
							curTurn.influentFigure = shared_ptr<Figure>(new Figure(figures[colour / White][rookNumber]));
							allMoves.push_back(curTurn);
						}
					}
				}
			}break;
			case Figure::Type::Queen:
			{
				for (int j = 0; j < BOARD_SIZE; ++j)
				{
					cur = figures[colour / White][i].get()->getPosition();
					cur.x += moveQueenX[j];
					cur.y += moveQueenY[j];
					while (!outOfBoard(cur))
					{
						curTurn.posToGo = cur;
						if (empty(cur))
						{
							curTurn.moveType = Common;
							curTurn.effectOnKing = None;
							curTurn.inflNumber = -1;
							curTurn.influentFigure = nullptr;
							allMoves.push_back(curTurn);
						}
						else
						{
							if (posFigures[cur.x][cur.y].posInVector / White != colour / White)
							{
								curTurn.moveType = Eat;
								int tNumber = posFigures[cur.x][cur.y].posInVector -
									(posFigures[cur.x][cur.y].posInVector / White + 1)*Black;
								if (figures[posFigures[cur.x][cur.y].posInVector / White][tNumber].get()->getType() == Figure::King)
									curTurn.effectOnKing = Mate;
								else
									curTurn.effectOnKing = None;
								curTurn.inflNumber = tNumber;
								curTurn.influentFigure =
									shared_ptr<Figure>(new Figure(figures[posFigures[cur.x][cur.y].posInVector / White][tNumber]));
								allMoves.push_back(curTurn);
							}
							break;
						}
						cur.x += moveQueenX[j];
						cur.y += moveQueenY[j];
					}
				}
			}break;
			case Figure::Type::Rook:
			{
				for (int j = 0; j < BOARD_SIZE / 2; ++j)
				{
					cur = figures[colour / White][i].get()->getPosition();
					cur.x += moveRookX[j];
					cur.y += moveRookY[j];
					while (!outOfBoard(cur))
					{
						curTurn.posToGo = cur;
						if (empty(cur))
						{
							curTurn.moveType = Common;
							curTurn.effectOnKing = None;
							curTurn.inflNumber = -1;
							curTurn.influentFigure = nullptr;
							allMoves.push_back(curTurn);
						}
						else
						{
							if (posFigures[cur.x][cur.y].posInVector / White != colour / White)
							{
								curTurn.moveType = Eat;
								int number = posFigures[cur.x][cur.y].posInVector - (posFigures[cur.x][cur.y].posInVector / White + 1)*Black;
								if (figures[posFigures[cur.x][cur.y].posInVector / White][number].get()->getType() == Figure::King)
									curTurn.effectOnKing = Mate;
								else
									curTurn.effectOnKing = None;
								curTurn.inflNumber = number;
								curTurn.influentFigure =
									shared_ptr<Figure>(new Figure(figures[posFigures[cur.x][cur.y].posInVector / White][number]));
								allMoves.push_back(curTurn);
							}
							break;
						}
						cur.x += moveRookX[j];
						cur.y += moveRookY[j];
					}
				}
			}break;
			case Figure::Type::Knight:
			{
				for (int j = 0; j < BOARD_SIZE; ++j)
				{
					cur = figures[colour / White][i].get()->getPosition();
					cur.x += moveKnightX[j];
					cur.y += moveKnightY[j];
					if (!outOfBoard(cur))
					{
						curTurn.posToGo = cur;
						if (empty(cur))
						{
							curTurn.moveType = Common;
							curTurn.effectOnKing = None;
							curTurn.inflNumber = -1;
							curTurn.influentFigure = nullptr;
							allMoves.push_back(curTurn);
						}
						else
						{
							if (posFigures[cur.x][cur.y].posInVector / White != colour / White)
							{
								curTurn.moveType = Eat;
								int number = posFigures[cur.x][cur.y].posInVector - (posFigures[cur.x][cur.y].posInVector / White + 1)*Black;
								if (figures[posFigures[cur.x][cur.y].posInVector / White][number].get()->getType() == Figure::King)
									curTurn.effectOnKing = Mate;
								else
									curTurn.effectOnKing = None;
								curTurn.inflNumber = number;
								curTurn.influentFigure =
									shared_ptr<Figure>(new Figure(figures[posFigures[cur.x][cur.y].posInVector / White][number]));
								allMoves.push_back(curTurn);
							}
						}
					}
				}
			}break;
			case Figure::Type::Bishop:
			{
				for (int j = 0; j < BOARD_SIZE/2; ++j)
				{
					cur = figures[colour / White][i].get()->getPosition();
					cur.x += moveBishopX[j];
					cur.y += moveBishopY[j];
					while (!outOfBoard(cur))
					{
						curTurn.posToGo = cur;
						if (empty(cur))
						{
							curTurn.moveType = Common;
							curTurn.effectOnKing = None;
							curTurn.inflNumber = -1;
							curTurn.influentFigure = nullptr;
							allMoves.push_back(curTurn);
						}
						else
						{
							if (posFigures[cur.x][cur.y].posInVector / White != colour / White)
							{
								curTurn.moveType = Eat;
								int number = posFigures[cur.x][cur.y].posInVector - (posFigures[cur.x][cur.y].posInVector / White + 1)*Black;
								if (figures[posFigures[cur.x][cur.y].posInVector / White][number].get()->getType() == Figure::King)
									curTurn.effectOnKing = Mate;
								else
									curTurn.effectOnKing = None;
								curTurn.inflNumber = number;
								curTurn.influentFigure =
									shared_ptr<Figure>(new Figure(figures[posFigures[cur.x][cur.y].posInVector / White][number]));
								allMoves.push_back(curTurn);
							}
							break;
						}
						cur.x += moveBishopX[j];
						cur.y += moveBishopY[j];
					}
				}
			}break;
			case Figure::Type::Pawn:
			{
				cur = figures[colour / White][i].get()->getPosition();
				int step = 1;
				if (colour == White)
					step = -1;
				cur.x += step;
				if (empty(cur))
				{
					curTurn.effectOnKing = None;
					curTurn.posToGo = cur;
					if (cur.x != 0 || cur.x != BOARD_SIZE - 1)
					{
						curTurn.moveType = Common;
						curTurn.inflNumber = -1;
						curTurn.influentFigure = nullptr;
						allMoves.push_back(curTurn);
						if (cur.x - step == 1 || cur.x - step == BOARD_SIZE - 2)
						{
							cur.x += step;
							if (empty(cur))
							{
								curTurn.posToGo = cur;
								curTurn.moveType = Common;
								allMoves.push_back(curTurn);
							}
						}
					}
					else
					{
						curTurn.moveType = NewFigure;
						curTurn.newFigure = Figure::Queen;
						curTurn.inflNumber = -1;
						curTurn.influentFigure = nullptr;
						allMoves.push_back(curTurn);
						curTurn.newFigure = Figure::Knight;
						allMoves.push_back(curTurn);
					}
				}
				for (int j = -1; j <= 1; ++j)
				{
					if (j == 0)
						continue;
					cur = figures[colour / White][i].get()->getPosition();
					cur.x += step; cur.y += j;
					if (outOfBoard(cur))
						continue;
					if (!empty(cur))
					{
						if (posFigures[cur.x][cur.y].posInVector / White != colour / White)
						{
							curTurn.posToGo = cur;
							int tColour = posFigures[cur.x][cur.y].posInVector / White;
							int tNumber = posFigures[cur.x][cur.y].posInVector - (tColour + 1)*Black;
							if (figures[tColour][tNumber].get()->getType() == Figure::King)
								curTurn.effectOnKing = Mate;
							else
								curTurn.effectOnKing = None;
							curTurn.influentFigure = shared_ptr<Figure>(new Figure(figures[tColour][tNumber]));
							curTurn.inflNumber = tNumber;
							if (cur.x == 0 || cur.x == BOARD_SIZE - 1)
							{
								curTurn.moveType = NewFigure;
								curTurn.newFigure = Figure::Queen;
								allMoves.push_back(curTurn);
								curTurn.newFigure = Figure::Knight;
								allMoves.push_back(curTurn);
							}
							else
							{
								curTurn.moveType = Eat;
								allMoves.push_back(curTurn);
							}
						}
					}
					else
					{
						int tColour = (colour%White + Black) / White;
						if (prevFigureNumber != -1 && figures[tColour][prevFigureNumber].get()->getType() == Figure::Pawn)
						{
							if (cur.x - step == 3 && colour == White || cur.x - step == 4 && colour == Black)
							{
								if (abs(prevFigurePos.x - figures[tColour][prevFigureNumber].get()->getPosition().x) == 2 &&
									cur.y == prevFigurePos.y)
								{
									curTurn.posToGo = cur;
									curTurn.effectOnKing = None;
									curTurn.moveType = EnPassant;
									curTurn.inflNumber = prevFigureNumber;
									curTurn.influentFigure = shared_ptr<Figure>(new Figure(figures[tColour][prevFigureNumber]));
									allMoves.push_back(curTurn);
								}
							}
						}

					}
				}
			}break;
			}
		}
	}
	myTurnSort(allMoves, weight);
	return allMoves;
}

vector<shared_ptr<Figure>> Board::getWhiteFigures()
{
	return figures[1];
}

vector<shared_ptr<Figure>> Board::getBlackFigures()
{
	return figures[0];
}

bool Board::getGameType()
{
	return gameType;
}

void Board::setGameType(bool x)
{
	gameType = x;
}

Figure::Colour Board::getWhoseTurn()
{
	return whoseTurn;
}

Board::MoveType Board::lastMoveType()
{
	return prevFigureMove.first;
}

int Board::lastMoveFigure()
{
	return prevFigureNumber + whoseTurnId % White + Black;
}

Vector2i Board::getSpecialFigurePos()
{
	if (prevFigureMove.first == Castling)
	{
		int t_colour = eatEnPassantCastlingFigure / White;
		int t_number = eatEnPassantCastlingFigure - (t_colour + 1)*Black;
		return figures[t_colour][t_number].get()->getPosition();
	}
	else
	{
		Vector2i curPos = figures[whoseTurn / White + Black][prevFigureNumber].get()->getPosition();
		if (whoseTurn / White + Black == Black)
			return curPos + Vector2i(-1, 0);
		else
			return curPos + Vector2i(1, 0);
	}
}

int Board::getSpecialFigure()
{
	return eatEnPassantCastlingFigure;
}

int Board::getPrevFigureNumber()
{
	return prevFigureNumber;
}

pair<Board::MoveType, Board::EffectOnKing> Board::getPrevFigureMove()
{
	return prevFigureMove;
}

Vector2i Board::getPrevFigurePos()
{
	return prevFigurePos;
}

int Board::isEndOfGame()
{
	return endOfGame;
}


void Board::changePositions(int movingFigure, Vector2i endPosBoard, Board::MoveType curMoveType, Figure::Type curType)
{
	Vector2i posMoveFigure = figures[0][movingFigure].get()->getPosition();

	if (curMoveType == Eat || curMoveType == EnPassant ||
		curMoveType == NewFigure && posFigures[endPosBoard.x][endPosBoard.y].posInVector == -1)
	{
		int tempFig;
		if (curMoveType == EnPassant)
		{
			tempFig = prevFigureNumber + White;
			posFigures[prevFigurePos.x][prevFigurePos.y].posInVector = -1;
		}
		else
		{
			tempFig = posFigures[endPosBoard.x][endPosBoard.y].posInVector;
			posFigures[endPosBoard.x][endPosBoard.y].posInVector = -1;
		}
		int number = tempFig - White;
		eatEnPassantCastlingFigure = tempFig;
		figures[1][number].reset();
	}
	else
		eatEnPassantCastlingFigure = -1;
	posFigures[endPosBoard.x][endPosBoard.y] = posFigures[posMoveFigure.x][posMoveFigure.y];
	posFigures[posMoveFigure.x][posMoveFigure.y].posInVector = -1;
	figures[0][movingFigure].get()->setPosition(endPosBoard);
	prevFigureNumber = movingFigure;
	prevFigurePos = posMoveFigure;
	prevFigureMove.first = curMoveType;
}

void Board::setWhoseTurn(Figure::Colour colour)
{
	whoseTurn = colour;
}



void Board::makeMoveComputer(TurnStruct turn)
{
	figures[turn.colour / White][turn.number].get()->setPosition(turn.posToGo);
	figures[turn.colour / White][turn.number].get()->setMoved();
	posFigures[turn.posToGo.x][turn.posToGo.y] = posFigures[turn.posFromGo.x][turn.posFromGo.y];
	posFigures[turn.posToGo.x][turn.posToGo.y].posInVector = -1;
	prevFigureNumber = turn.number;
	prevFigurePos = turn.posFromGo;
	if (turn.inflNumber != -1)
		eatEnPassantCastlingFigure = turn.influentFigure.get()->getColourId() + turn.inflNumber;
	else
		eatEnPassantCastlingFigure = -1;
	prevFigureMove.first = turn.moveType;
	prevFigureMove.second = turn.effectOnKing;
	whoseTurnId = whoseTurn % White + Black;
	if (turn.moveType == Eat || turn.moveType == EnPassant)
		figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber].reset();
	else if (turn.moveType == NewFigure)
	{
		if (turn.inflNumber != -1)
			figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber].reset();
		figures[turn.colour / White][turn.number].get()->setType(turn.newFigure);
	}
	else if (turn.moveType == Castling)
	{
		Vector2i tempPos = (turn.posFromGo + turn.posToGo) / 2;
		figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber].get()->setPosition(tempPos);
		figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber].get()->setMoved();
	}
}

void Board::unMakeMoveComputer(TurnStruct turn)
{
	figures[turn.colour / White][turn.number].get()->setPosition(turn.posFromGo);
	if (!turn.moved)
		figures[turn.colour / White][turn.number].get()->setDeMoved();
	posFigures[turn.posFromGo.x][turn.posFromGo.y] = posFigures[turn.posToGo.x][turn.posToGo.y];
	posFigures[turn.posToGo.x][turn.posToGo.y].posInVector = -1;
	whoseTurnId = whoseTurn % White + Black;
	if (turn.moveType == Eat || turn.moveType == EnPassant)
	{
		figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber] = turn.influentFigure;
	}
	else if (turn.moveType == NewFigure)
	{
		if (turn.inflNumber != -1)
			figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber] = turn.influentFigure;
		figures[turn.colour / White][turn.number].get()->setType(Figure::Pawn);
	}
	else if (turn.moveType == Castling)
	{
		figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber].get()->
			setPosition(turn.influentFigure.get()->getPosition());
		figures[turn.influentFigure.get()->getColourId() / White][turn.inflNumber].get()->setDeMoved();
	}
}

Vector2i Board::getKingPos(Figure::Colour colour)
{
	int king = getKingNumber(Colour(colour));
	return figures[colour/White][king].get()->getPosition();
}

shared_ptr<Figure> Board::getFigureInPos(int x, int y)
{
	int number = posFigures[x][y].posInVector;
	if (number == -1)
		return nullptr;
	int colour = number / White;
	number = number - (colour + 1)*Black;
	return figures[colour][number];
}

Board::~Board()
{
}