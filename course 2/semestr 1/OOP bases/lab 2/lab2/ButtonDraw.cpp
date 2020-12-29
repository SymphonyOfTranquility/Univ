#include "ButtonDraw.h"

ButtonDraw::ButtonDraw(shared_ptr<ButtonDraw> base)
{
	button = base.get()->get_button();
	is_picture = false;
	texture.reset();
	sprite.reset();
	is_text = true;
	font = shared_ptr<Font>(new Font);
	text = shared_ptr<Text>(new Text);
	font.get()->loadFromFile("arial.ttf");
	text.get()->setFont(*font);
	text.get()->setCharacterSize(base.get()->get_size_font());
	text.get()->setString("");
	text.get()->setStyle(Text::Regular);
	text.get()->setPosition((float)button.position_height, (float)button.position_width);
}

ButtonDraw::ButtonDraw(ifstream &fin, string window_name)
{
	getline(fin, button.button_name);
	getline(fin, button.button_name);
	getline(fin, button.button_name);
	button.window_name = window_name;
	fin >> button.position_width >> button.position_height >> button.width >> button.height;
	fin >> is_picture;
	string file_picture_name;
	if (is_picture) {
		getline(fin, file_picture_name);
		getline(fin, file_picture_name);
		texture = shared_ptr<Texture>(new Texture);
		texture.get()->loadFromFile(file_picture_name);
		sprite = shared_ptr<Sprite>(new Sprite);
		sprite.get()->setTexture(*texture);
		sprite.get()->setPosition(Vector2f((float)button.position_height, (float)button.position_width));
	}
	else
		file_picture_name = "";
	fin >> is_text;
	if (is_text)
	{
		font = shared_ptr<Font>(new Font);
		font.get()->loadFromFile("arial.ttf");
		text = shared_ptr<Text>(new Text);
		text.get()->setFont(*font);
		int size_font;
		fin >> size_font;
		text.get()->setCharacterSize(size_font);
		if (button.button_name == "Title")	
			text.get()->setString(button.window_name);
		else 
			text.get()->setString(button.button_name);
		text.get()->setStyle(Text::Regular);
		text.get()->setPosition(Vector2f((float)button.position_height, (float)button.position_width));
		fin >> button.color_r >> button.color_g >> button.color_b;
		fin >> button.color_undcur_r >> button.color_undcur_g >> button.color_undcur_b;
	}
}

void ButtonDraw::unpress()
{
	button.is_pressed = false;
}

void ButtonDraw::unfocus()
{
	button.is_under_cursor = false;
}

void ButtonDraw::draw(shared_ptr<RenderWindow> window)
{
	if (is_picture)
		window.get()->draw(*sprite);
	if (is_text)
	{
		if (button.is_under_cursor) 
			text.get()->setFillColor(Color(button.color_undcur_r, button.color_undcur_g, button.color_undcur_b));
		else
			text.get()->setFillColor(Color(button.color_r,button.color_g,button.color_b));
		window.get()->draw(*text);
	}
	//window.reset();
}

void ButtonDraw::mouse_is_there(int pos_w, int pos_h)
{
	if (in_it(pos_w, pos_h))
		button.is_under_cursor = true;
	else
		button.is_under_cursor = false;
}

void ButtonDraw::mouse_is_pressed(int pos_w, int pos_h, shared_ptr<RenderWindow> window, bool is_pressed)
{
	if (in_it(pos_w, pos_h) && is_pressed || button.is_pressed)
	{
		if (button.button_name == "Title")
		{
			if (!button.is_pressed) {
				button.prev_pos_mouse_h = pos_h;
				button.prev_pos_mouse_w = pos_w;
			}
			button.is_pressed = true;
			window.get()->setPosition(Vector2i(Mouse::getPosition().x - button.prev_pos_mouse_h, Mouse::getPosition().y - button.prev_pos_mouse_w));
			button.prev_pos_mouse_h = Mouse::getPosition(*window).x;
			button.prev_pos_mouse_w = Mouse::getPosition(*window).y;
		}
	}
}

void ButtonDraw::mouse_is_released(int pos_w, int pos_h, shared_ptr<RenderWindow> window, int & need_to_create_window)
{
	if (in_it(pos_w, pos_h)) 
	{
	//	cout << button.button_name << '\n' << pos_w << ' ' << pos_h << '\n';
		if (button.button_name == "Cross") 
			window.get()->close();
		else if (button.button_name == "Simple Probability")
			need_to_create_window = 1;
		else if (button.button_name == "Walk on the graph")
			need_to_create_window = 2;
	}
}

void ButtonDraw::set_text(double num, bool add_to_name, bool is_int) 
{
	string s = "";
	if (is_int)
	{
		int temp = (int)num;
		while (temp > 0)
		{
			s += '0' + temp % 10;
			temp /= 10;
		}
		reverse(s.begin(), s.end());
		s += '.';
	}
	else {
		s = to_string(num);
		while (s.length() > 6)
			s.pop_back();
		if (s[s.length() - 1] == '.')
			s.pop_back();
	}

	if (add_to_name)
		s = button.button_name + s + " result is ";

	text.get()->setString(s);
	text.get()->setOrigin(Vector2f((float)(s.length() == 2 ? -2.f : 0)*5.f, 0.f));
}

void ButtonDraw::set_text(string s)
{
	text.get()->setString(s);
}

void ButtonDraw::set_position(int pos_w, int pos_h)
{
	button.position_height = pos_h;
	button.position_width = pos_w;

	text.get()->setPosition(Vector2f((float)pos_h, (float)pos_w));
	text.get()->setString(button.button_name);
}

void ButtonDraw::add_value(double value)
{
	string s = to_string(value);
	s.pop_back();
	s.pop_back();
	s.pop_back();
	s = " " + s;
	s = button.button_name + s;
	text.get()->setString(s);
}

string ButtonDraw::get_name()
{
	return button.button_name;
}

characteristic_of_button ButtonDraw::get_button()
{
	return button;
}

shared_ptr<Font> ButtonDraw::get_font()
{
	return font;
}

int ButtonDraw::get_size_font()
{
	return text.get()->getCharacterSize();
}

ButtonDraw::~ButtonDraw()
{
	text.reset();
	font.reset();
	sprite.reset();
	texture.reset();
}
