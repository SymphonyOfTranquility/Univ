#pragma once
#include <string>

using namespace std;

struct characteristic_of_button
{
	string button_name, window_name;

	int position_width, position_height;
	int width, height;
	int color_r, color_g, color_b;
	int color_undcur_r, color_undcur_g, color_undcur_b;

	bool is_released, is_pressed, is_under_cursor;
	int prev_pos_mouse_w, prev_pos_mouse_h;
	characteristic_of_button();
};


class Button
{

protected:
	characteristic_of_button button;
public:
	Button();
	bool in_it(int pos_w,int pos_h);
	~Button();
};

