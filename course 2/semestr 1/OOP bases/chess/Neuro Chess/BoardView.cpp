#include "BoardView.h"



BoardView::BoardView()
{
	board = shared_ptr<Board>(new Board);
	renderBoard = shared_ptr<RenderTexture>(new RenderTexture);
	renderBoard.get()->create(PIXEL_SIZE * BOARD_SIZE, PIXEL_SIZE * BOARD_SIZE);
	figureTexture = shared_ptr<Texture>(new Texture);
	figureTexture.get()->loadFromFile("Data\\chess.png");
	figureSprite = shared_ptr<Sprite>(new Sprite);
	figureSprite.get()->setTexture(*figureTexture);

	vector<shared_ptr<Figure> > tempFigures = board.get()->getBlackFigures();
	shared_ptr<FigureView> tempFigureView;
	for (int i = 0; i < tempFigures.size(); ++i)
	{
		tempFigureView = shared_ptr<FigureView>(new FigureView(tempFigures[i]));
		viewOfFigures[0].push_back(tempFigureView);
	}

	tempFigures = board.get()->getWhiteFigures();
	for (int i = 0; i < tempFigures.size(); ++i)
	{
		tempFigureView = shared_ptr<FigureView>(new FigureView(tempFigures[i]));
		viewOfFigures[1].push_back(tempFigureView);
	}
	boardSprite = shared_ptr<Sprite>(new Sprite);
	boardSprite.get()->setPosition(25.f, 25.f);
	isUnderMouse = -1;

	algoGame = shared_ptr<AlgoGame>(new AlgoGame);
	newWindow = "";
	attention = false;
	textOfEnd = "";
}

void BoardView::draw(shared_ptr<RenderWindow> &window)
{
	renderBoard.get()->clear(Color(0, 0, 0, 0));
	Vector2i posInTexture;
	Vector2f posInWindow;
	for (int curColour = 0; curColour < 2; ++curColour) 
	{
		for (int i = 0; i < viewOfFigures[curColour].size(); ++i)
		{
			if (i == isUnderMouse && curColour == underMouseColour)
				continue;
			if (viewOfFigures[curColour][i].get() != nullptr)
			{
				posInTexture = viewOfFigures[curColour][i].get()->getPosInTexture();
				posInWindow = viewOfFigures[curColour][i].get()->getPosInWindow();
				figureSprite.get()->setTextureRect(IntRect(posInTexture, Vector2i(PIXEL_SIZE, PIXEL_SIZE)));
				figureSprite.get()->setPosition(posInWindow);
				renderBoard.get()->draw(*figureSprite);
			}
		}
	}
	if (isUnderMouse != -1)
	{
		posInTexture = viewOfFigures[underMouseColour][isUnderMouse].get()->getPosInTexture();
		posInWindow = viewOfFigures[underMouseColour][isUnderMouse].get()->getPosInWindow();
		figureSprite.get()->setTextureRect(IntRect(posInTexture, Vector2i(PIXEL_SIZE, PIXEL_SIZE)));
		figureSprite.get()->setPosition(posInWindow);
		renderBoard.get()->draw(*figureSprite);
	}
	renderBoard.get()->display();
	boardSprite.get()->setTexture(renderBoard.get()->getTexture());
	window.get()->draw(*boardSprite);
}

void BoardView::pollEvent(Event event, shared_ptr<RenderWindow>& window)
{
	if (!board.get()->isEndOfGame() && board.get()->getWhoseTurn() == Figure::Colour::Black && !board.get()->getGameType()
		|| board.get()->getWhoseTurn() == Figure::Colour::White)
	{
		if (event.type == Event::MouseButtonPressed)
		{
			checkMousePressedFigure(Mouse::getPosition(*window) - offSet);
		}
		if (event.type == Event::MouseButtonReleased)
		{
			checkMouseReleasedFigure();
		}

		if (isUnderMouse != -1 && newWindow == "")
		{
			checkMousePressedFigure(Mouse::getPosition(*window) - offSet);
		}
	}
}

void BoardView::withoutEvent()
{
	endOfGame();
	if (!board.get()->isEndOfGame() && board.get()->getGameType() && board.get()->getWhoseTurn() == Figure::Colour::Black)
	{
		if (algoGame.get()->madeMove())
		{
			int numberOFMovingFigure = algoGame.get()->getMovingFigure();
			Vector2f tempAfterLaw = algoGame.get()->figureLawMove(viewOfFigures[0][numberOFMovingFigure].get()->getPosInWindow());
			viewOfFigures[0][numberOFMovingFigure].get()->setPosition(tempAfterLaw);
		}
		else if (algoGame.get()->getEndOfMove())
		{
			board.get()->changePositions(algoGame.get()->getMovingFigure(), algoGame.get()->getEndPosBoard(), 
				algoGame.get()->getMoveType(), algoGame.get()->getNewFigureType());
			algoGame.get()->setEndOfMove(false);
			board.get()->setWhoseTurn(Figure::Colour::White);
			for (int j = 0; j < 2; ++j)
				for (int i = 0; i < (int)viewOfFigures[0].size(); ++i)
					if (viewOfFigures[j][i] != nullptr && viewOfFigures[j][i].get()->getFigure().use_count() == 2)
						viewOfFigures[j][i].reset();
			endOfGame();
		}
		else
		{
			shared_ptr<Board> temp = shared_ptr<Board>(new Board(board));
			algoGame.get()->moveComputer(temp);
		}
	}

}

bool BoardView::checkMousePressedFigure(Vector2i mousePos)
{
	if (!checkMouseOutOfBoard(mousePos) || board == nullptr)
		false;
	if (isUnderMouse == -1)
	{
		for (int curColour = 0; curColour < 2; ++curColour)
		{
			for (int i = 0; i < viewOfFigures[curColour].size(); ++i)
			{
				if (viewOfFigures[curColour][i].get() != nullptr && viewOfFigures[curColour][i].get()->isUnderMouse(mousePos))
				{
					if (viewOfFigures[curColour][i].get()->getFigureColorId() == board.get()->getWhoseTurn())
					{
						isUnderMouse = i;
						underMouseColour = curColour;
						break;
					}
				}
			}
		}
	}
	if (isUnderMouse != -1)
	{
		viewOfFigures[underMouseColour][isUnderMouse].get()->setMousePosition(mousePos);
		return true;
	}
	else
		return false;
}

void BoardView::checkMouseReleasedFigure()
{
	if (isUnderMouse != -1)
	{
		Vector2i tempPosFigure = Vector2i(viewOfFigures[underMouseColour][isUnderMouse].get()->getPosInWindow()) +
			Vector2i(PIXEL_SIZE, PIXEL_SIZE) / 2;
		swap(tempPosFigure.x,tempPosFigure.y);
		if (board.get()->checkCanLeftThere(isUnderMouse, tempPosFigure/PIXEL_SIZE))
		{
			swap(tempPosFigure.x, tempPosFigure.y);
			viewOfFigures[underMouseColour][isUnderMouse].get()->setCellPosition(tempPosFigure);
			if (board.get()->lastMoveType() == Board::MoveType::Castling)
			{
				Vector2i castlFigurePos = board.get()->getSpecialFigurePos();
				swap(castlFigurePos.x, castlFigurePos.y);
				int castlFigure = board.get()->getSpecialFigure();
				int castlFigureColour = castlFigure / Board::Colour::White;
				int castlingFigureInArr = castlFigure - (castlFigureColour + 1)*Board::Colour::Black;
				viewOfFigures[castlFigureColour][castlingFigureInArr].get()->setCellPosition(castlFigurePos*PIXEL_SIZE);
			}
			if (board.get()->lastMoveType() == Board::MoveType::Eat || 
				board.get()->lastMoveType() == Board::MoveType::EnPassant)
			{
				int eatenFigure = board.get()->getSpecialFigure();
				int eatenFigureColour = eatenFigure / Board::Colour::White;
				int eatenFigureInArr = eatenFigure - (eatenFigureColour + 1)*Board::Colour::Black;
				viewOfFigures[eatenFigureColour][eatenFigureInArr].reset();
			}
			if (board.get()->lastMoveType() == Board::MoveType::NewFigure)
			{
				newWindow = "figures for change";
				int eatenFigure = board.get()->getSpecialFigure();
				if (eatenFigure != -1) 
				{
					int eatenFigureColour = eatenFigure / Board::Colour::White;
					int eatenFigureInArr = eatenFigure - (eatenFigureColour + 1)*Board::Colour::Black;
					viewOfFigures[eatenFigureColour][eatenFigureInArr].reset();
				}
			}
		}
		else
			viewOfFigures[underMouseColour][isUnderMouse].get()->setCellPrevPosition();
	}
	isUnderMouse = -1;
}

bool BoardView::checkMouseOutOfBoard(Vector2i mousePos)
{
	return (0 <= mousePos.x && mousePos.x <= PIXEL_SIZE * BOARD_SIZE
		&& 0 <= mousePos.y && mousePos.y <= PIXEL_SIZE * BOARD_SIZE);
}

bool BoardView::getGameType()
{
	return board.get()->getGameType();
}

void BoardView::setGameType(bool typeGame)
{
	board.get()->setGameType(typeGame);
}

void BoardView::endOfGame()
{
	board.get()->checkMateDraw();
	if (board.get()->isEndOfGame() && !attention)
	{
		attention = true;
		newWindow = "endOfGame";
		if (board.get()->isEndOfGame() == 1)
		{
			if (board.get()->getWhoseTurn() == Figure::Colour::Black)
				textOfEnd = "White wins!!!";
			else
				textOfEnd = "Black wins!!!";
		}
		else
			textOfEnd = "  Stalemate";
	}
}

string BoardView::getTextOfEnd()
{
	string temp = textOfEnd;
	textOfEnd = "";
	return temp;
}


string BoardView::needNewWindow()
{
	string temp = newWindow;
	newWindow = "";
	return temp;
}

Figure::Colour BoardView::getWhoseTurn()
{
	return board.get()->getWhoseTurn();
}

void BoardView::setFigureType(Figure::Type type)
{
	int tempFigure = board.get()->lastMoveFigure();
	int colour = tempFigure / Board::Colour::White;
	int number = tempFigure-(colour + 1)*Board::Colour::Black;
	viewOfFigures[colour][number].get()->setType(type);
	viewOfFigures[colour][number].get()->getFigure()->setType(type);
	//board.get()->setWhoseTurn(Figure::Colour((int)board.get()->getWhoseTurn() % 128 + 64));
}

BoardView::~BoardView()
{
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < viewOfFigures[j].size(); ++i)
			viewOfFigures[j][i].reset();
	board.reset();
	renderBoard.reset();
	figureTexture.reset();
}