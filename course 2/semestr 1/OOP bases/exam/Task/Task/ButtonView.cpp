#include "ButtonView.h"



ButtonView::ButtonView(ifstream &fin, shared_ptr<Button> curButton)
{
	button = curButton;

	int red, green, blue, transparrent;
	bool ok;
	fin >> ok;
	if (ok)
	{
		texture = true;
		string s;
		getline(fin, s);
		while (s == "")
			getline(fin, s);
		buttonTexture = shared_ptr<Texture>(new Texture);
		buttonTexture.get()->loadFromFile(s);
		sprite = shared_ptr<Sprite>(new Sprite);
		sprite.get()->setTexture(*buttonTexture);
		sprite.get()->setPosition(button.get()->getPosition());
	}
	fin >> ok;
	if (ok)
	{
		background = true;
		fin >> red >> green >> blue >> transparrent;
		colorBackground = shared_ptr<Color>(new Color(red, green, blue, transparrent));
		fin >> red >> green >> blue >> transparrent;
		colorBackgroundUnderCursor = shared_ptr<Color>(new Color(red, green, blue, transparrent));
		fin >> red >> green >> blue >> transparrent;
		colorBackgroundPressed = shared_ptr<Color>(new Color(red, green, blue, transparrent));
		if (!texture)
		{
			renderBackground = shared_ptr<RenderTexture>(new RenderTexture);
			renderBackground.get()->create(button.get()->getSize().x, button.get()->getSize().y);
			renderBackground.get()->clear(Color::White);
			buttonTexture = shared_ptr<Texture>(new Texture(renderBackground.get()->getTexture()));
			sprite = shared_ptr<Sprite>(new Sprite);
			sprite.get()->setTexture(*buttonTexture);
			sprite.get()->setPosition(button.get()->getPosition());
		}
	}
	fin >> ok;
	if (ok)
	{
		frame = true;
		fin >> red >> green >> blue >> transparrent;
		colorFrame = shared_ptr<Color>(new Color(red, green, blue, transparrent));
		fin >> red >> green >> blue >> transparrent;
		colorBackgroundUnderCursor = shared_ptr<Color>(new Color(red, green, blue, transparrent));
		fin >> red >> green >> blue >> transparrent;
		colorFramePressed = shared_ptr<Color>(new Color(red, green, blue, transparrent));
		buttonFrame = shared_ptr<VertexArray>(new VertexArray);
		shared_ptr<Vertex> tempVertex = shared_ptr<Vertex>(new Vertex);
		Vector2f pos = button.get()->getPosition() + Vector2f(0.5f, 0.5f);
		tempVertex.get()->color = *colorFrame;
		tempVertex.get()->position = pos;
		buttonFrame.get()->append(*tempVertex);

		tempVertex = shared_ptr<Vertex>(new Vertex);
		pos.x = button.get()->getPosition().x + float(button.get()->getSize().x) - 0.5f;
		tempVertex.get()->position = pos;
		buttonFrame.get()->append(*tempVertex);

		tempVertex = shared_ptr<Vertex>(new Vertex);
		pos.y = button.get()->getPosition().y + float(button.get()->getSize().y) - 0.5f;
		tempVertex.get()->position = pos;
		buttonFrame.get()->append(*tempVertex);

		tempVertex = shared_ptr<Vertex>(new Vertex);
		pos.x = button.get()->getPosition().x + 0.5f;
		tempVertex.get()->position = pos;
		buttonFrame.get()->append(*tempVertex);

		tempVertex = shared_ptr<Vertex>(new Vertex);
		pos.y = button.get()->getPosition().y + 0.5f;
		tempVertex.get()->position = pos;
		buttonFrame.get()->append(*tempVertex);

		buttonFrame.get()->setPrimitiveType(LinesStrip);
	}
	fin >> ok;
	if (ok)
	{
		text = true;
		font = shared_ptr<Font>(new Font);
		font.get()->loadFromFile("Data\\Inconsolata.ttf");
		buttonText = shared_ptr<Text>(new Text);
		buttonText.get()->setFont(*font);
		int sizeFont;
		fin >> sizeFont;
		buttonText.get()->setCharacterSize(sizeFont);
		string s;
		getline(fin, s);
		while (s == "")
			getline(fin, s);
		buttonText.get()->setString(s);
		buttonText.get()->setStyle(Text::Regular);
		buttonText.get()->setPosition(button.get()->getPosition());
		fin >> red >> green >> blue >> transparrent;
		colorText = shared_ptr<Color>(new Color(red, green, blue, transparrent));
		buttonText.get()->setFillColor(*colorText);
	}
}

void ButtonView::draw(shared_ptr<RenderTexture> &window)
{
	if (texture)
	{
		if (background)
		{
			if (button.get()->isUnderCursor() && !button.get()->isPressed() ||
				!button.get()->isUnderCursor() && button.get()->isPressed())
				sprite.get()->setColor(*colorBackgroundUnderCursor);
			else if (button.get()->isPressed())
				sprite.get()->setColor(*colorBackgroundPressed);
			else
				sprite.get()->setColor(*colorBackground);
		}
		window.get()->draw(*sprite);
	}
	else if (background)
	{
		if (button.get()->isUnderCursor() && !button.get()->isPressed() ||
			!button.get()->isUnderCursor() && button.get()->isPressed())
			sprite.get()->setColor(*colorBackgroundUnderCursor);
		else if (button.get()->isPressed())
			sprite.get()->setColor(*colorBackgroundPressed);
		else
			sprite.get()->setColor(*colorBackground);
		window.get()->draw(*sprite);
	}
	if (frame)
	{
		VertexArray temp = (*buttonFrame);
		if (button.get()->isUnderCursor() && !button.get()->isPressed() ||
			!button.get()->isUnderCursor() && button.get()->isPressed())
			temp[0].color = temp[1].color = temp[2].color = temp[3].color = temp[4].color = *colorBackgroundUnderCursor;
		else if (button.get()->isPressed())
			temp[0].color = temp[1].color = temp[2].color = temp[3].color = temp[4].color = *colorFramePressed;
		else
			temp[0].color = temp[1].color = temp[2].color = temp[3].color = temp[4].color = *colorFrame;

		window.get()->draw(temp);
	}
	if (text)
	{
		window.get()->draw(*buttonText);
	}

}

string ButtonView::getName()
{
	return button->getName();
}

bool ButtonView::isPressed()
{
	return button.get()->isPressed();
}

void ButtonView::dePressed()
{
	button.get()->dePressed();
}

bool ButtonView::isReleased()
{
	return button.get()->isReleased();
}

void ButtonView::deReleased()
{
	button.get()->deReleased();
}

bool ButtonView::isUnderCursor()
{
	return button.get()->isUnderCursor();
}

void ButtonView::deUnderCursor()
{
	button.get()->deUnderCursor();
}

void ButtonView::setText(string curText)
{
	buttonText.get()->setString(curText);
}


ButtonView::~ButtonView()
{
}
