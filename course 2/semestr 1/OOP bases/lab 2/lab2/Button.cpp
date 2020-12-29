#include "Button.h"

characteristic_of_button::characteristic_of_button()
{
	window_name = button_name = "";
	position_height = position_width = width = height = 0;
	is_pressed = is_released = is_under_cursor = false;
	color_r = color_g = color_b = 0;
	color_undcur_r = color_undcur_g = color_undcur_b = 0;
	prev_pos_mouse_w = prev_pos_mouse_h = 0;
}

Button::Button()
{
}

bool Button::in_it(int pos_w, int pos_h)
{
	if (button.position_width <= pos_w && pos_w <= button.position_width + button.width &&
		button.position_height <= pos_h && pos_h <= button.position_height + button.height)
		return true;
	else
		return false;
}

Button::~Button()
{
}
