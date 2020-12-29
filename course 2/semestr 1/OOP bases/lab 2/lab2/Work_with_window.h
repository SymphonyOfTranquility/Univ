#pragma once
#include "ButtonDraw.h"
#include "Input_field.h"
#include "Algorithm_simple_probability.h"
#include "Algorithm_graph.h"
#include "Visualisation_of_graph.h"

#include <SFML/Graphics.hpp>
#include <fstream>

using namespace sf;
using namespace std;

class Work_with_window
{
	shared_ptr<RenderWindow> window;
	vector<shared_ptr<ButtonDraw> > base_buttons;
	vector<shared_ptr<ButtonDraw> > buttons;
	vector<shared_ptr<Input_field> > base_fields;
	vector<shared_ptr<Input_field> > fields;
	
	shared_ptr<Algorithm_simple_probability> algo_simple;
	shared_ptr<Algorithm_graph> algo_graph;
	shared_ptr<Visualisation_of_graph> show_graph;

	string information;
	int need_to_create_window;
	int number_of_created_windows_type_2;
	bool saved, created, showed;

	void check_buttons_under_cursor(int pos_w, int pos_h);
	void check_buttons_is_pressed(int pos_w, int pos_h, bool is_pressed);
	void check_buttons_is_released(int pos_w, int pos_h);
	void check_button_go_simple(bool what);
	void check_button_go_in_graph(int index); 
	void check_button_save_vertexes();
	void check_last_on_neg_simple(int index);

	void check_fields_under_cursor(int pos_w, int pos_h);
	void check_fields_is_released(int pos_w, int pos_h);

	void check_fields_entered_text(char temp);
	void check_fields_save_open(char temp);
	void check_fields_backspace();
	void check_fields_tab();
	void check_fields_on_last_dot_simple(); 
	void check_fields_on_last_dot_graph();
	void check_last_prob_field(); 
	void check_last_vertex_prob_field(); 
	void check_del_play_pause();

	void create_fields(int number); 
	void create_fields_graph(int number);
	void create_tests(int number);
	void help_create_tests();

	bool button_enter_values_simple();
	bool button_enter_values_graph();
	void help_enter_values_simple();
	int get_pos_base_button(string val); 
	int get_pos_base_fields(string val);
	void delete_buttons_simple(int i);
	void delete_buttons_in_graph(int number);
	void render_opened_file(ifstream &fin);

public:
	Work_with_window();
	Work_with_window(string &file);
	void work();
	void draw_frame_for_window(shared_ptr<RenderWindow> window);
	void draw();
	int need_new_window();
	bool is_open();
	~Work_with_window();
};

