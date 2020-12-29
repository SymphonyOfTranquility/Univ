#include "Visualisation_of_graph.h"

const double pi = 3.1415926535;

void Visualisation_of_graph::next_values(double &x, double &y, double center_x, double center_y, double len, double rad)
{
	if (abs(center_x - x) < 0.0001)
	{
		y = (len*len - rad * rad) / (2 * (center_y - y)) + (center_y + y)/2;
		x = sqrt(rad*rad - (y - center_y)*(y - center_y)) + center_x;		
		bool ok = true;
		for (int j = 0; j < vertexes.size(); ++j)
		{
			Vector2f vec = vertexes[j].get()->getPosition();
			if (abs(vec.x - x) < 0.0001 && abs(vec.y - y) < 0.0001)
			{
				ok = false;
				break;
			}
		}
		if (!ok)
			x = -sqrt(rad*rad - (y - center_y)*(y - center_y)) + center_x;
	}
	else if (abs(center_y - y) < 0.0001)
	{
		x = (len*len - rad * rad) / (2 * (center_x - x)) + (center_x + x)/2;
		y = sqrt(rad*rad - (x - center_x)*(x - center_x)) + center_y;
		bool ok = true;
		for (int j = 0; j < vertexes.size(); ++j)
		{
			Vector2f vec = vertexes[j].get()->getPosition();
			if (abs(vec.x - x) < 0.0001 && abs(vec.y - y) < 0.0001)
			{
				ok = false;
				break;
			}
		}
		if (!ok)
			y = -sqrt(rad*rad - (x - center_x)*(x - center_x)) + center_y;
	}
	else
	{
		double temp = rad * rad - len * len + y * y - center_y * center_y + x * x - center_x * center_x;
		double l = -(y - center_y) / (x - center_x), m = temp / (2 * (x - center_x))- center_x;
		double z = (l*l + 1),
			p = 2 * (l*m - center_y),
			q = m * m + center_y * center_y - rad * rad;
		double D = p * p - 4 * q*z;
		D = sqrt(D);
		y = (-p + D) / (2 * z);
		x = m + center_x + y * l;
		bool ok = true;
		for (int j = 0; j < vertexes.size(); ++j)
		{
			Vector2f vec = vertexes[j].get()->getPosition();
			if (abs(vec.x - x) < 0.0001 && abs(vec.y - y) < 0.0001)
			{
				ok = false;
				break;
			}
		}
		if (!ok)
		{
			y = (-p - D) / (2 * z);
			x = m + center_x + y * l;
		}
	}
}

double Visualisation_of_graph::vertex_distance(int from, int to)
{
	Vector2f v_from = vertexes[from - 1].get()->getPosition();
	Vector2f v_to = vertexes[to - 1].get()->getPosition();
	return sqrt((v_from.x-v_to.x)*(v_from.x - v_to.x)+ (v_from.y - v_to.y)*(v_from.y - v_to.y));
}

Vector2f Visualisation_of_graph::get_edge_position(int from, int to)
{
	Vector2f v_from = vertexes[from - 1].get()->getPosition();
	Vector2f v_to = vertexes[to - 1].get()->getPosition();
	Vector2f ans;
	ans.x = (float) ((v_from.x + v_to.x) / 2.0);
	ans.y = (float) ((v_from.y + v_to.y) / 2.0);
	return ans;
}

float Visualisation_of_graph::get_angle_for_edge(int from, int to)
{
	Vector2f v_from = vertexes[from - 1].get()->getPosition();
	Vector2f v_to = vertexes[to - 1].get()->getPosition();
	float x = abs(v_from.x - v_to.x);
	float y = abs(v_from.y - v_to.y);
	if (v_from.x - v_to.x == 0)
		return 90;
	else {
		float angle = (float)atan((float)(y / x));
		if ((v_from.x - v_to.x)*(v_from.y - v_to.y) > 0)
			return float (angle*180.f/pi);
		else //if ((v_from.x - v_to.x)*(v_from.y - v_to.y) < 0)
			return float (-angle*180.f/pi);
	}
}

float Visualisation_of_graph::get_angle_arrow(int from, int to, float angle_edge)
{
	Vector2f v_from = vertexes[from - 1].get()->getPosition();
	Vector2f v_to = vertexes[to - 1].get()->getPosition();
	if (angle_edge == 0) {
		if (v_from.x < v_to.x)
			return 90.f;
		else
			return -90.f;
	}
	else if (angle_edge == 90) 
	{
		if (v_from.y < v_to.y)
			return 180.f;
		else
			return 0.f;
	}
	else if (angle_edge < 0)
	{
		if (v_from.x < v_to.x)
			return angle_edge + 90.f;
		else
			return angle_edge - 90.f;
	}
	else
	{
		if (v_from.x < v_to.x)
			return angle_edge + 90.f;
		else
			return angle_edge - 90.f;
	}
}

Vector2f Visualisation_of_graph::get_position_for_arrow(float angle, float dist, int from, int to)
{
	Vector2f v_from = vertexes[from - 1].get()->getPosition();
	Vector2f v_to = vertexes[to - 1].get()->getPosition();
	Vector2f ans;
	if (angle >= 0)
	{
		if (v_to.x < v_from.x)
		{
			ans.x = float (v_to.x + dist * cos(angle*pi / 180));
			ans.y = float (v_to.y + dist * sin(angle*pi / 180));
		}
		else if (v_to.x > v_from.x)
		{
			ans.x = float (v_to.x - dist * cos(angle*pi / 180));
			ans.y = float (v_to.y - dist * sin(angle*pi / 180));
		}
		else if (v_to.y < v_from.y)
		{
			ans.x = v_to.x;
			ans.y = v_to.y + dist;
		}	
		else
		{
			ans.x = v_to.x;
			ans.y = v_to.y - dist;
		}
	}
	else {
		angle = -angle;
		if (v_to.x < v_from.x)
		{
			ans.x = float(v_to.x + dist * cos(angle*pi / 180));
			ans.y = float(v_to.y - dist * sin(angle*pi / 180));
		}
		else
		{
			ans.x = float(v_to.x - dist * cos(angle*pi / 180));
			ans.y = float(v_to.y + dist * sin(angle*pi / 180));
		}
	}
	return ans;
}

void Visualisation_of_graph::change_pointer_position_on_edge()
{
	Vector2f prev_pos = pointer.get()->getPosition();
	Vector2f next_pos;
	if (line_b != 0) {
		next_pos.x = prev_pos.x + move_where;
		next_pos.y = (-line_a * next_pos.x - line_c) / line_b;
	}
	else {
		next_pos.y = prev_pos.y + move_where;
		next_pos.x = (-line_b * next_pos.y - line_c) / line_a;
	}
	pointer.get()->setPosition(next_pos);
	//cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%  " << current_vertex << ' ' << have_to << '\n';
	//cout << vertexes[current_vertex - 1].get()->getPosition().x << ' ' << vertexes[current_vertex - 1].get()->getPosition().y <<  '\n';
	//cout << next_pos.x << "   " << vertexes[have_to - 1].get()->getPosition().x << ' ' << move_where;
	//cout << "\n_______ " << next_pos.y << "   " << vertexes[have_to - 1].get()->getPosition().y << ' ' << '\n';
	if (abs(next_pos.x - vertexes[have_to - 1].get()->getPosition().x) <= 3.0 &&
		abs(next_pos.y - vertexes[have_to - 1].get()->getPosition().y) <= 3.0)
	{
		line_a = line_b = line_c = 0;
		in_move_on_edge = false;
	}
}

void Visualisation_of_graph::count_line()
{
	Vector2f v_from = vertexes[current_vertex - 1].get()->getPosition();
	Vector2f v_to = vertexes[have_to - 1].get()->getPosition();
	line_a = (v_to.y - v_from.y);
	line_b = -v_to.x + v_from.x;
	line_c = (-v_from.x*v_to.y + v_from.y*v_to.x);
	double dist = vertex_distance(current_vertex, have_to) / 3.0;
	if (v_to.x > v_from.x)
		move_where = abs(v_to.x - v_from.x) / dist;
	else if (v_to.x < v_from.x)
		move_where = abs(v_to.x - v_from.x) / (-dist);
	else if (v_to.y > v_from.y)
		move_where = abs(v_to.y - v_from.y) / dist;
	else 
		move_where = abs(v_to.y - v_from.y) / (-dist);
	pointer.get()->setPosition(v_from);
}

void Visualisation_of_graph::change_color(shared_ptr<Algorithm_graph> graph)
{
	int index = graph.get()->find_edge(current_vertex, have_to);
	Color edge_color = edges[index].first.get()->getFillColor();
	int sub = 15;
	edge_color.g = (edge_color.g - sub >= 0 ? edge_color.g - sub : 0);
	edge_color.b = (edge_color.b - sub >= 0 ? edge_color.b - sub : 0);
	if (edge_color.g == 0)
		edge_color.r = (edge_color.r - sub >= 0 ? edge_color.r - sub : 0);
	edges[index].first.get()->setFillColor(edge_color);

	edge_color = edges[index].second.get()->getFillColor();
	edge_color.g = (edge_color.g - sub >= 0 ? edge_color.g - sub : 0);
	edge_color.b = (edge_color.b - sub >= 0 ? edge_color.b - sub : 0);
	if (edge_color.g == 0)
		edge_color.r = (edge_color.r - sub >= 0 ? edge_color.r - sub : 0);
	edges[index].second.get()->setFillColor(edge_color);
}


Visualisation_of_graph::Visualisation_of_graph(shared_ptr<Algorithm_graph> graph)
{
	image = shared_ptr<RenderTexture>(new RenderTexture);
	image.get()->create(450, 450);
	int n = graph.get()->get_size();
	double len = 65, rad = (n == 1 ? 0 : len / (2 * sin(pi / n))), angle = 2 * pi / n;
	double x = 225, y = 225-rad, center_x = 225, center_y = 225;
	shared_ptr<CircleShape> temp;
	shared_ptr<Text> temp_text;
	font = shared_ptr<Font>(new Font);
	font.get()->loadFromFile("arial.ttf");
	for (int i = 0; i < n; ++i)
	{
	//	cout << x << ' ' << y << '\n';
		temp = shared_ptr<CircleShape>(new CircleShape);
		temp.get()->setRadius(14.f);
		temp.get()->setOutlineThickness(2.f);
		temp.get()->setFillColor(Color(40, 40, 40, 170));
		temp.get()->setOutlineColor(Color(0,200,200));
		temp.get()->setOrigin(14.f, 14.f);
		temp.get()->setPosition((float)x, (float)y);
		vertexes.push_back(temp);
	
		temp_text = shared_ptr<Text>(new Text);
		temp_text.get()->setFont(*font);
		temp_text.get()->setString(to_string(i + 1));
		temp_text.get()->setCharacterSize(20);
		if (i + 1 < 10)
			temp_text.get()->setOrigin(6.f, 12.f);
		else if (i + 1 < 20)
			temp_text.get()->setOrigin(12.5f, 12.f);
		else
			temp_text.get()->setOrigin(11.f, 12.f);


		temp_text.get()->setPosition((float)x, (float)y);
		number.push_back(temp_text);

		next_values(x, y, center_x, center_y, len, rad);
	}
	vector<pair<int, int> > edge = graph.get()->get_all_edges(); 
	shared_ptr<RectangleShape> temp_edge;
	shared_ptr<CircleShape> arrow;
	for (int i = 0; i < edge.size(); ++i)
	{
		double dist = vertex_distance(edge[i].first, edge[i].second);
		temp_edge = shared_ptr<RectangleShape>(new RectangleShape(Vector2f(float(dist - 28.f), 2.f)));
		temp_edge.get()->setOrigin(float(dist / 2.0 - 14.f), 1.f);
		temp_edge.get()->setPosition(get_edge_position(edge[i].first, edge[i].second));
		temp_edge.get()->setFillColor(Color(255, 255, 255));
		float angle = get_angle_for_edge(edge[i].first, edge[i].second);
		temp_edge.get()->setRotation(angle);
		arrow = shared_ptr<CircleShape>(new CircleShape(7.f, 3));
		arrow.get()->setOrigin(7.f, 7.f);
		arrow.get()->setRotation(get_angle_arrow(edge[i].first, edge[i].second, angle));
		arrow.get()->setPosition(get_position_for_arrow(angle, 21, edge[i].first, edge[i].second));
		edges.push_back({ temp_edge,arrow });
	}

	pointer = shared_ptr<CircleShape>(new CircleShape(8.f, 10));
	pointer.get()->setOrigin(8.f, 8.f);
	Vector2f temp_pos = vertexes[0].get()->getPosition();
//	temp_pos.x -= 25;
	pointer.get()->setPosition(temp_pos);
	pointer.get()->setFillColor(Color(255, 0, 0));

	start_time = high_resolution_clock::now();
	last_time = 0.f;
	in_move_on_edge = can_move = false;
	have_to = current_vertex = 1;
	move_on_circle = true;
}

void Visualisation_of_graph::draw(shared_ptr<RenderWindow> window)
{
	image.get()->clear(Color(10, 10, 10, 0));
	for (int i = 0; i < (int)edges.size(); ++i) 
	{
		Vector2f pos_1 = edges[i].first.get()->getPosition(), pos_2;
		float angle_1 = edges[i].first.get()->getRotation(), angle_2;
		shared_ptr<RectangleShape> temp = edges[i].first;
		for (int j = 0;j < (int)edges.size(); ++j)
			if (i != j)
			{
				pos_2 = edges[j].first.get()->getPosition();
				angle_2 = edges[j].first.get()->getRotation();
				if (abs(pos_2.x - pos_1.x) <= 1 && abs(pos_2.y - pos_1.y) <= 1 &&
					(abs(angle_1 - angle_2) <= 0.1 || abs(abs(angle_1 - angle_2) - 180.0) <= 0.1))
				{
					Color color_1 = edges[i].first.get()->getFillColor(), color_2 = edges[j].first.get()->getFillColor();
					if (color_1.b > color_2.b)
						temp = edges[j].first;
					else if (color_1.b == 0 && color_1.r > color_2.r)
						temp = edges[j].first;
				}
			}
		image.get()->draw(*temp);
	}
	for (int i = 0; i < (int)edges.size(); ++i)
		image.get()->draw(*edges[i].second);
	image.get()->draw(*pointer);
	for (int i = 0; i < (int)vertexes.size(); ++i)
	{
		image.get()->draw(*vertexes[i]);
		image.get()->draw(*number[i]);
	}
	image.get()->draw(*pointer);
	image.get()->display();
	Texture temp_texture;
	temp_texture = image.get()->getTexture();
	Sprite temp_sprite;
	temp_sprite.setTexture(temp_texture);
	temp_sprite.setPosition(340,50);
	window.get()->draw(temp_sprite);
}

void Visualisation_of_graph::move(shared_ptr<Algorithm_graph> graph)
{
	if (can_move)
	{
		high_resolution_clock::time_point current = high_resolution_clock::now();
		auto duration = duration_cast<chrono::microseconds>(current - start_time).count();
		double dur_in_sec = double (duration) / 1000000.0;
		if (dur_in_sec - last_time > 0.0001)
		{
			last_time = dur_in_sec;
			if (in_move_on_edge)
			{
				change_pointer_position_on_edge();
				if (!in_move_on_edge)
					move_on_circle = true;
			}
			else if (move_on_circle)
			{
				if (line_a == line_b && line_a == 0) 
				{
					if (current_vertex != have_to)
						change_color(graph);
					current_vertex = have_to;
					have_to = graph.get()->get_next_vertex();
					if (have_to != -1) {
						count_line();
						move_on_circle = false;
						in_move_on_edge = true;
					}
					else {
						move_on_circle = false;
						in_move_on_edge = false;
					}
				}
			}
		}
	}
}

void Visualisation_of_graph::un_move()
{
	can_move = false;
}

void Visualisation_of_graph::canmove()
{
	can_move = true;
}


Visualisation_of_graph::~Visualisation_of_graph()
{
	for (int i = (int)vertexes.size()-1;i >= 0; --i)
	{
		vertexes[i].reset();
		number[i].reset();
		vertexes.pop_back();
		number.pop_back();
	}
	for (int j = (int)edges.size() - 1; j >= 0; --j) 
	{
		edges[j].first.reset();
		edges[j].second.reset();
		edges.pop_back();
	}
	image.reset();
	font.reset();
	pointer.reset();
}
