#pragma once
#include "Button.h"

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Input_field :
	public Button
{
	using Button::button;

	shared_ptr<Texture> texture;
	shared_ptr<Texture> texture_in_action;
	shared_ptr<Sprite> sprite;
	
	bool has_focus;

	string text_value;
	int int_value;
	double double_value;
	shared_ptr<Text> text;
	shared_ptr<Font> font;

	void render_texture(ifstream &fin, shared_ptr<RenderTexture> temp_render);
	void convert_to_int();
	bool convert_to_double();

public:

	Input_field(shared_ptr<Input_field> base);
	Input_field(ifstream &fin, string window_name);
	void draw(shared_ptr<RenderWindow> window);
	void is_under_cursor(int pos_w, int pos_h);
	void mouse_is_released(int pos_w, int pos_h);
	
	bool _has_focus();
	void unfocus();
	void gain_focus();

	int _int_value();
	void add_text(char c, bool is_graph, int value = -1);
	void add_char_text(char c);
	void del_el_string();
	void check_on_dot();
	void last_field_counter(double counter, bool all_filled);

	void set_position(int pos_w, int pos_h);
	void set_text(string s, bool is_int = true);

	characteristic_of_button get_button();
	shared_ptr<Texture> get_texture();
	shared_ptr<Texture> get_texture_in_action();
	shared_ptr<Font> get_font();
	int get_text_size();
	int get_text_value_length();
	string get_field_name(); 
	string get_text_value();
	double get_double_value();

	void clear_text();


	bool field_criterion_in_graph(int value, int num);

	~Input_field();
};

