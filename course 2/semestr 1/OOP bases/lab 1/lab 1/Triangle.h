#ifndef _TRIANGLE_H_USED
#define _TRIANGLE_H_USED

#include "Polygon.h"

class Triangle: public Polygon
{
public:
	Triangle();
	Triangle(pair<double, double> p[3]);
	Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
	void set_points(pair<double, double> p[3]);
	void set_points(double x1, double y1, double x2, double y2, double x3, double y3);
	double square();
	double perimetr();
	string regular();
	void my_rand();
	friend ostream& operator<<(ostream& os, const Triangle& value);
	friend istream& operator>>(istream& is, Triangle& value);
	~Triangle();
};

#endif

