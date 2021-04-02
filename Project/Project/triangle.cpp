#include"triangle.h"
#include <math.h>
#include <iostream>
using namespace std;

Triangle::Triangle(vector<Point> vertexes)
{
	set_vertexes(vertexes);
	init_area();
	init_perimeter();
}
Triangle::~Triangle() {

}

bool Triangle::operator== (const Triangle& t) const {
	bool f = distance(_p1, _p2) == distance(t._p1, t._p2) && distance(_p2, _p3) == distance(t._p2, t._p3) && distance(_p1, _p3) == distance(t._p1, t._p3);
	return f;
}
bool Triangle::operator!= (const Triangle& t) const {
	bool f = distance(_p1, _p2) != distance(t._p1, t._p2) || distance(_p2, _p3) != distance(t._p2, t._p3) || distance(_p1, _p3) != distance(t._p1, t._p3);
	return f;
}

Segment middle_line(Triangle const& t)
{
	int k;
	Point p1 = t.get_vertex(0), p2 = t.get_vertex(1), p3 = t.get_vertex(2);
	Point k1, k2;
	Segment s1 = Segment(p1, p2), s2 = Segment(p2, p3), s3 = Segment(p3, p1);
	cout << "Input the side you want the middle line be parallel to\n";
	cout << "1." << p1 << " " << p2 << endl;
	cout << "2." << p2 << " " << p3 << endl;
	cout << "3." << p3 << " " << p1 << endl;
	cin >> k;
	if (k >= 1 && k <= 3)
	{
		if (k == 1)
		{
			k1 = s3.midpoint(s3);
			k2 = s2.midpoint(s2);
		}
		else if (k == 2)
		{
			k1 = s1.midpoint(s1);
			k2 = s3.midpoint(s3);
		}
		else if (k == 3)
		{
			k1 = s2.midpoint(s2);
			k2 = s1.midpoint(s1);
		}
		return Segment(k1, k2);
	}
	return Segment();
}