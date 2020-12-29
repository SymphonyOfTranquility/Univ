#include "Tetragon.h"

Tetragon::Tetragon()
{
	for (int i = 0; i < 4; ++i)
		points[i].x = points[i].y = 0;
}

void Tetragon::set_points(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	points[0].x = x1;
	points[1].x = x2;
	points[2].x = x3;
	points[3].x = x4;
	points[0].y = y1;
	points[1].y = y2;
	points[2].y = y3;
	points[3].y = y4;
	for (int i = 0; i < 4; ++i)
		side[i] = size_of_side(points[i], points[(i + 1) % 4]);
}

void Tetragon::set_points(pair<double, double> p[4])
{
	for (int i = 0; i < 4; ++i) {
		points[i].x = p[i].first;
		points[i].y = p[i].second;
	}
	for (int i = 0;i < 4; ++i)
		side[i] = size_of_side(points[i], points[(i + 1) % 4]);
}

Tetragon::Tetragon(double x1, double y1, double x2, double y2, double x3, double y3, double x4,double y4)
{
	set_points(x1, y1, x2, y2, x3, y3, x4, y4);
}
Tetragon::Tetragon(pair<double, double> p[4])
{
	set_points(p);
}

double Tetragon::square()
{
	double sum = 0;
	for (int i = 0; i < 4; ++i)
		sum += points[i].x*points[(i + 1) % 4].y - points[i].y * points[(i + 1) % 4].x;
	return abs(0.5*sum);
}

double Tetragon::perimetr()
{
	return side[0] + side[1] + side[2] + side[3];
}


string Tetragon::regular()
{
	if (abs(side[1] + side[2] + side[3] - side[0] < eps) ||
		abs(side[2] + side[3] + side[0] - side[1] < eps) ||
		abs(side[3] + side[0] + side[1] - side[2] < eps)||
		abs(side[0] + side[1] + side[2] - side[3] < eps))
		return "Degenerated";
	else if (abs(side[0] - side[1]) < eps && abs(side[1] - side[2]) < eps && abs(side[2] - side[3]) < eps)
	{
		if (abs(angle(0,4) - angle(1,4)) < eps)
			return "Square";
		else
			return "Rhombus";
	}
	else if (abs(side[0] - side[2]) < eps &&  abs(side[1] - side[3]) < eps)
	{
		if (abs(angle(1,4)) < eps)
			return "Rectangle";
		else
			return "Parallelogram";
	}
	else if (abs(angle(3,4) + angle(4,4)) < eps && abs(angle(1,4) + angle(2,4)) < eps ||
		abs(angle(2,4) + angle(3,4)) < eps && abs(angle(0,4) + angle(1,4)) < eps)
		return "Trapezoid";
	return "Other";
}

void Tetragon::my_rand()
{
	for (int i = 0; i < 4; ++i) 
	{
		points[i].x = (double)rand() / RAND_MAX * 100.0;
		points[i].y = (double)rand() / RAND_MAX * 100.0;
	}
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < 2; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (j == i || j == (i + 1) % 4 || j == (i + 3) % 4)
					continue;
				if (crossed_line(i, j, 4))
				{
					points[(j + 1) % 4].x = (double)rand() / RAND_MAX * 100.0;
					points[(j + 1) % 4].y = (double)rand() / RAND_MAX * 100.0;
					flag = true;
					break;
				}
			}
			if (flag)
				break;
		}
	}
	for (int i = 0; i < 4; ++i)
		side[i] = size_of_side(points[i], points[(i + 1) % 4]);
}


Tetragon::~Tetragon()
{
}

ostream & operator<<(ostream & os, const Tetragon & value)
{
	Tetragon temp = value;
	os << "( " << temp.points[0].x << ";" << temp.points[0].y << " )";
	for (int i = 1; i < 4; ++i)
		os << ",( " << temp.points[i].x << ";" << temp.points[i].y << " )";
	os << " Square = " << temp.square() << ", Perimetr = " << temp.perimetr() << ", Type = " << temp.regular();
	return os;
}

istream & operator>>(istream & is, Tetragon & value)
{
	for (int i = 0; i < 4; ++i)
		is >> value.points[i].x >> value.points[i].y;
	for (int i = 0; i < 4; ++i)
		value.side[i] = value.size_of_side(value.points[i], value.points[(i + 1) % 4]);
	return is;
}
