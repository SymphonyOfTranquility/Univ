#pragma once
#include "Algorithm_graph.h"

#include <SFML/Graphics.hpp>
#include <chrono>

using namespace sf;
using namespace std;
using namespace std::chrono;

class Visualisation_of_graph
{
	shared_ptr<RenderTexture> image;
	vector<shared_ptr<CircleShape> > vertexes;
	vector<shared_ptr<Text> > number;
	vector<pair<shared_ptr<RectangleShape>, shared_ptr<CircleShape> > > edges;
	shared_ptr<CircleShape> pointer;	
	shared_ptr<Font> font;
	bool can_move, in_move_on_edge, move_on_circle;
	high_resolution_clock::time_point start_time;
	double last_time;
	double line_a, line_b, line_c;
	double move_where;
	int have_to, current_vertex;

	void next_values(double &x, double &y, double center_x, double center_y, double len, double rad);
	double vertex_distance(int from, int to); 
	Vector2f get_edge_position(int from, int to);
	float get_angle_for_edge(int from, int to);
	float get_angle_arrow(int from, int to, float angle_edge);
	Vector2f get_position_for_arrow(float angle, float dist, int from, int to);
	void change_pointer_position_on_edge();
	void count_line();
	void change_color(shared_ptr<Algorithm_graph> graph);
public:
	Visualisation_of_graph(shared_ptr<Algorithm_graph> graph);
	void draw(shared_ptr<RenderWindow> window);
	void move(shared_ptr<Algorithm_graph> graph);
	void un_move();
	void canmove();
	~Visualisation_of_graph();
};

