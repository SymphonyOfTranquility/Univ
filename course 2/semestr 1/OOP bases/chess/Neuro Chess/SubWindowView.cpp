#include "SubWindowView.h"



void SubWindowView::checkButtonIsPressed(shared_ptr<RenderWindow> &window, Vector2i mousePos, bool checkPressed)
{
	if (checkPressed || subWindow.get()->checkButtonIsPressed(mousePos))
	{
		int buttonNumber = -1;
		for (int i = 0; i < (int)buttons.size(); ++i)
		{
			if (buttons[i].get()->isPressed())
			{
				buttonNumber = i;
				break;
			}
		}
		if (buttonNumber != -1 && buttons[buttonNumber].get()->getName() == "Title")
		{
			if (prevMousePos == Vector2i(-1, -1))
				prevMousePos = Mouse::getPosition() - window.get()->getPosition();
			window.get()->setPosition(Mouse::getPosition() - prevMousePos);
			//prevMousePos = Mouse::getPosition();
		}
		else
			prevMousePos = Vector2i(-1, -1);
	}
}

void SubWindowView::checkButtonIsReleased(shared_ptr<RenderWindow>& window, Vector2i mousePos, shared_ptr<BoardView> &board)
{
	if (subWindow.get()->checkButtonIsReleased(mousePos))
	{
		int buttonNumber = -1;
		for (int i = 0; i < (int)buttons.size(); ++i)
		{
			if (buttons[i].get()->isReleased())
			{
				buttonNumber = i;
				break;
			}
		}
		if (buttonNumber != -1)
		{
			if (buttons[buttonNumber].get()->getName() == "Close")
				window.get()->close();
			else if (buttons[buttonNumber].get()->getName() == "Update")
				newWindow = "Update";
			else if (buttons[buttonNumber].get()->getName() == "Settings")
				newWindow = "Settings";
			else if (subWindow.get()->getName() == "Update")
			{
				if (buttons[buttonNumber].get()->getName() == "No")
					subWindow.get()->deActive();
				else if (buttons[buttonNumber].get()->getName() == "Yes")
				{
					bool gameType = board.get()->getGameType();
					board = shared_ptr<BoardView>(new BoardView);
					board.get()->setGameType(gameType);
					subWindow.get()->deActive();
				}
			}
			else if (subWindow.get()->getName() == "Settings")
			{
				if (buttons[buttonNumber].get()->getName() == "Exit")
					subWindow.get()->deActive();
				else
				{
					board = shared_ptr<BoardView>(new BoardView);
					if (buttons[buttonNumber].get()->getName() == "Person vs Person")
						board.get()->setGameType(false);
					else
						board.get()->setGameType(true);
					subWindow.get()->deActive();
				}
			}
			else if (subWindow.get()->getName() == "endOfGame")
			{
				if (buttons[buttonNumber].get()->getName() == "Ok!")
					subWindow.get()->deActive();
			}
			else if (subWindow.get()->getName() == "figures for change")
			{
				if (buttons[buttonNumber].get()->getName() == "Queen")
					board.get()->setFigureType(Figure::Type::Queen);
				else if (buttons[buttonNumber].get()->getName() == "Rook")
					board.get()->setFigureType(Figure::Type::Rook);
				else if (buttons[buttonNumber].get()->getName() == "Knight")
					board.get()->setFigureType(Figure::Type::Knight);
				else
					board.get()->setFigureType(Figure::Type::Bishop);

				subWindow.get()->deActive();
			}
			buttons[buttonNumber].get()->deReleased();
		}
	}
	else
	{
		for (int i = 0; i < (int)buttons.size(); ++i)
		{
			buttons[i].get()->dePressed();
			buttons[i].get()->deReleased();
		}
	}
}

void SubWindowView::checkButtonIsUnderCursor(shared_ptr<RenderWindow>& window, Vector2i mousePos)
{
	if (!subWindow.get()->checkButtonIsUnderCursor(mousePos))
	{
		//cout << "_____________________\n";
		for (int i = 0; i < (int)buttons.size(); ++i)
			buttons[i].get()->deUnderCursor();
	}
}

SubWindowView::SubWindowView(ifstream &fin)
{
	bool ok;
	fin >> ok;
	if (ok)
	{
		background = true;
		backgroundTexture = shared_ptr<Texture>(new Texture);
		string backgroundName;
		getline(fin, backgroundName);
		while (backgroundName == "")
			getline(fin, backgroundName);
		backgroundTexture.get()->loadFromFile(backgroundName);
		backgroundSprite = shared_ptr<Sprite>(new Sprite);
		backgroundSprite.get()->setTexture(*backgroundTexture);
		backgroundSprite.get()->setPosition({ 0.f,0.f });
	}
	else
		background = false;

	subWindow = shared_ptr<SubWindow>(new SubWindow(fin));
	if (subWindow.get()->getName() == "Board")
	{
		subWindow.get()->setActive();
		subWindow.get()->setFocus();
	}
	string dataButtonView;
	getline(fin, dataButtonView);
	while (dataButtonView == "")
		getline(fin, dataButtonView);
	ifstream ffin(dataButtonView);
	vector<shared_ptr<Button> > allButtons = subWindow.get()->getAllButtons();
	shared_ptr<ButtonView> tempButton;
	for (int i = 0; i < (int)allButtons.size(); ++i)
	{
		tempButton = shared_ptr<ButtonView>(new ButtonView(ffin, allButtons[i]));
		buttons.push_back(tempButton);
	}
	ffin.close();

	renderSubWindow = shared_ptr<RenderTexture>(new RenderTexture);
	renderSubWindow.get()->create(subWindow.get()->getSize().x, subWindow.get()->getSize().y);
	spriteSubWindow = shared_ptr<Sprite>(new Sprite);
	spriteSubWindow.get()->setPosition(subWindow.get()->getPosition());
	int red, green, blue, transparent;
	fin >> red >> green >> blue >> transparent;
	backgroundWindowColor = shared_ptr<Color>(new Color(red, green, blue, transparent));

	fin >> red >> green >> blue >> transparent;
	Color colorFrame = Color(red, green, blue, transparent);
	subWindowFrame = shared_ptr<VertexArray>(new VertexArray);
	shared_ptr<Vertex> tempVertex = shared_ptr<Vertex>(new Vertex);
	Vector2f pos = Vector2f(0.5f, 0.5f);
	tempVertex.get()->color = colorFrame;
	tempVertex.get()->position = pos;
	subWindowFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = colorFrame;
	pos.x = float(subWindow.get()->getSize().x) - 0.5f;
	tempVertex.get()->position = pos;
	subWindowFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = colorFrame;
	pos.y = float(subWindow.get()->getSize().y) - 0.5f;
	tempVertex.get()->position = pos;
	subWindowFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = colorFrame;
	pos.x = 0.5f;
	tempVertex.get()->position = pos;
	subWindowFrame.get()->append(*tempVertex);

	tempVertex = shared_ptr<Vertex>(new Vertex);
	tempVertex.get()->color = colorFrame;
	pos.y = 0.5f;
	tempVertex.get()->position = pos;
	subWindowFrame.get()->append(*tempVertex);

	subWindowFrame.get()->setPrimitiveType(LinesStrip);
	prevMousePos = Vector2i(-1, -1);
}

void SubWindowView::draw(shared_ptr<RenderWindow> &window)
{
	if (subWindow.get()->isActive())
	{
		renderSubWindow.get()->clear(*backgroundWindowColor);
		if (background)
			renderSubWindow.get()->draw(*backgroundSprite);
		renderSubWindow.get()->draw(*subWindowFrame);
		for (int i = 0; i < (int)buttons.size(); ++i)
			buttons[i].get()->draw(renderSubWindow);
		renderSubWindow.get()->display();
		spriteSubWindow.get()->setTexture(renderSubWindow.get()->getTexture());
		window.get()->draw(*spriteSubWindow);
	}
}


bool SubWindowView::isActive()
{
	return subWindow.get()->isActive();
}

void SubWindowView::setActive(string created)
{
	subWindow.get()->setActive(created);
}

void SubWindowView::setFocus()
{
	subWindow.get()->setFocus();
}

bool SubWindowView::hasFocus()
{
	return subWindow.get()->hasFocus();
}

void SubWindowView::deFocus()
{
	subWindow.get()->deFocus();
}

string SubWindowView::hasParent()
{
	return subWindow.get()->hasParent();
}

string SubWindowView::needNewWindow()
{
	string temp = newWindow;
	newWindow = "";
	return temp;
}

string SubWindowView::getName()
{
	return subWindow.get()->getName();
}

void SubWindowView::pollEvent(Event event, shared_ptr<RenderWindow> &window, shared_ptr<BoardView> &board)
{
	if (subWindow.get()->hasFocus())
	{
		if (event.type == Event::Closed)
			window.get()->close();
		if (subWindow.get()->getName() != "Board" && subWindow.get()->getName() != "endOfGame" 
			&& subWindow.get()->getName() != "figures for change"
			&& event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape))
			subWindow.get()->deActive();
		if (event.type == Event::MouseButtonPressed)
		{
			checkButtonIsPressed(window, Mouse::getPosition(*window), false);
		}
		if (event.type == Event::MouseButtonReleased)
		{
			checkButtonIsReleased(window, Mouse::getPosition(*window), board);
		}
	}
	else
	{
		for (int i = 0; i < (int)buttons.size(); ++i)
		{
			buttons[i].get()->dePressed();
			buttons[i].get()->deReleased();
			buttons[i].get()->deUnderCursor();
		}
	}
}

void SubWindowView::withoutEventButton(shared_ptr<RenderWindow>& window)
{
	if (subWindow.get()->hasFocus())
	{
		checkButtonIsUnderCursor(window, Mouse::getPosition(*window));
		checkButtonIsPressed(window, Mouse::getPosition(*window), true);
	}
}

void SubWindowView::setText(string text)
{
	buttons[0].get()->setText(text);
}

void SubWindowView::setRect(Figure::Colour colour)
{
	if (colour == Figure::Colour::White)
	{
		backgroundSprite.get()->setTextureRect(IntRect(0, 64, 256, 64));
	}
	else
	{
		backgroundSprite.get()->setTextureRect(IntRect(0, 0, 256, 64));
	}
}

SubWindowView::~SubWindowView()
{
}
