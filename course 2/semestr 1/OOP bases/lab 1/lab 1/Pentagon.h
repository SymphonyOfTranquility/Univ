#ifndef _PENTAGON_H_USED
#define _PENTAGON_H_USED

#include "Polygon.h"

class Pentagon :
	public Polygon
{
public:
	Pentagon();
	Pentagon(pair<double, double> p[5]);
	Pentagon(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5);
	void set_points(pair<double, double> p[5]);
	void set_points(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5);
	double square();
	double perimetr();
	string regular();
	void my_rand();
	friend ostream& operator<<(ostream& os, const Pentagon& value);
	friend istream& operator>>(istream& is, Pentagon& value);
	~Pentagon();
};

#endif