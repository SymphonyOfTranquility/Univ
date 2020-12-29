#include "Triangle.h"

Triangle::Triangle()
{
	for (int i = 0; i < 3; ++i)
		points[i].x = points[i].y = 0;
}

void Triangle::set_points(double x1, double y1, double x2, double y2, double x3, double y3)
{
	points[0].x = x1;
	points[1].x = x2;
	points[2].x = x3;
	points[0].y = y1;
	points[1].y = y2;
	points[2].y = y3;
	for (int i = 0; i < 3; ++i)
		side[i] = size_of_side(points[i], points[(i + 1) % 3]);
}

void Triangle::set_points(pair<double, double> p[3])
{
	for (int i = 0; i < 3; ++i) {
		points[i].x = p[i].first;
		points[i].y = p[i].second;
	}
	for (int i = 0; i < 3; ++i)
		side[i] = size_of_side(points[i], points[(i + 1) % 3]);
	
}

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	set_points(x1, y1, x2, y2, x3, y3);
}
Triangle::Triangle(pair<double, double> p[3])
{
	set_points(p);
}

double Triangle::square()
{
	double p = (side[0] + side[1] + side[2]) / 2;
	return sqrt(p*(p - side[0])*(p - side[1])*(p - side[2]));
}

double Triangle::perimetr()
{
	return side[0] + side[1] + side[2];
}

string Triangle::regular()
{
	if (abs(side[1] + side[2] - side[0]) < eps ||
		abs(side[2] + side[0] - side[1]) < eps ||
		abs(side[0] + side[1] - side[2]) < eps)
		return "Degenerated";
	else if (abs(side[0] - side[1]) < eps && abs(side[1] == side[2]) < eps)
		return "Equilateral";
	else if (abs(side[0] - side[1]) < eps && abs(angle(1,3)) < eps||
		abs(side[1] - side[2]) < eps && abs(angle(2,3)) < eps ||
		abs(side[2] - side[0]) < eps && abs(angle(0,3)) < eps)
		return "Isosceles Right";
	else if (abs(side[0] - side[1]) < eps || abs(side[1] - side[2]) < eps || abs(side[2] - side[0]) < eps)
		return "Isosceles";
	else if (abs(angle(0,3)) < eps || abs(angle(1,3)) < eps || abs(angle(2,3)) < eps)
		return "Right";
	else 
		return "Common";
}

void Triangle::my_rand()
{
	for (int i = 0; i < 3; ++i) {
		points[i].x = (double)rand() / RAND_MAX * 100.0;
		points[i].y = (double)rand() / RAND_MAX * 100.0;
	}
	for (int i = 0;i < 3; ++i)
		side[i] = size_of_side(points[i], points[(i + 1) % 3]);
}


ostream & operator<<(ostream & os, const Triangle & value)
{
	Triangle temp = value;
	os << "( " << temp.points[0].x << ";" << temp.points[0].y << " )";
	for (int i = 1; i < 3; ++i)
		os << ",( " << temp.points[i].x << ";" << temp.points[i].y << " )";
	os << " Square = " << temp.square() << ", Perimetr = " << temp.perimetr() << ", Type = " << temp.regular();
	return os;
}

istream & operator>>(istream & is, Triangle & value)
{
	for (int i = 0; i < 3; ++i)
		is >> value.points[i].x >> value.points[i].y;
	for (int i = 0; i < 3; ++i)
		value.side[i] = value.size_of_side(value.points[i], value.points[(i + 1) % 3]);
	return is;
}


Triangle::~Triangle()
{
}