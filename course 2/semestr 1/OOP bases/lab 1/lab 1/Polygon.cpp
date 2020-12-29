#include "Polygon.h"

double Polygon::size_of_side(Tpoint a, Tpoint b)
{
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}


bool Polygon::point_in_line_segment(int x, Tpoint point, int mod)
{
	return (points[x].x <= point.x && point.x <= points[(x + 1) % mod].x ||
		points[(x + 1) % mod].x <= point.x && point.x <= points[x].x) &&
		(points[x].y <= point.y && point.y <= points[(x + 1) % mod].y ||
			points[(x + 1) % mod].y <= point.y && point.y <= points[x].y);
}

bool Polygon::crossed_line(int line1, int line2, int mod)
{
	Tpoint temp;
	double a1 = (points[(line1 + 1) % 5].y - points[line1].y), b1 = (points[line1].x - points[(line1 + 1) % 5].x), 
		c1 = -a1 * points[line1].x - b1 * points[line1].y;
	double a2 = (points[(line2 + 1) % 5].y - points[line2].y), b2 = (points[line2].x - points[(line2 + 1) % 5].x),
		c2 = -a2 * points[line2].x - b2 * points[line2].y;
	temp.x = (b2*c1 - b1 * c2) / (a2*b1 - a1 * b2);
	temp.y = (b1 != 0 ? (-a1 * temp.x - c1) / b1 : (-a2 * temp.x - c2) / b2);
	return point_in_line_segment(line1, temp, 4) && point_in_line_segment(line2, temp, 4);
}

double Polygon::angle(int point,int mod)
{
	return (points[(point + mod-1) % mod].x - points[point].x)*(points[(point + 1) % mod].x - points[point].x) +
		(points[(point + mod-1) % mod].y - points[point].y)*(points[(point + 1) % mod].y - points[point].y) / (side[point] * side[(point + mod-1) % mod]);
}