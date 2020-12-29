#ifndef _POLYGON_H_USED
#define _POLYGON_H_USED


#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <random>

struct Tpoint { double x, y; };

using std::string;
using std::pair;
using std::cout;
using std::ostream;
using std::istream;

class Polygon
{
protected:
	const double eps = 0.00001;
	double side[5];
	Tpoint points[5];
	double size_of_side(Tpoint a, Tpoint b);
	bool point_in_line_segment(int line, Tpoint point,int mod);
	bool crossed_line(int line1, int line2, int mod);
	double angle(int point, int mod);
public:
	virtual double square() = 0;
	virtual double perimetr() = 0;
	virtual string regular() = 0;
	virtual void my_rand() = 0;
	virtual ~Polygon() {}
};


#endif