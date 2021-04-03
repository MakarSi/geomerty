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

void Triangle::set_vertexes(vector<Point> vertexes) {
	try
	{
		if (vertexes.size() > 3 || vertexes.size() == 0)
			throw "Try input vertexes again";
		if (vertexes.size() == 3 && (vertexes[2].get_x() - vertexes[0].get_x()) * (vertexes[1].get_y() - vertexes[0].get_y())
			== (vertexes[1].get_x() - vertexes[0].get_x()) * (vertexes[2].get_y() - vertexes[0].get_y()))
			throw "Error: A degenerate triangle!";

		for (size_t i = 0; i < vertexes.size(); i++)
			_vertexes.push_back(vertexes[i]);

	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		Point p(0, 0);
		_vertexes.push_back(p);
		_vertexes.push_back(p);
		_vertexes.push_back(p);
	}
}

bool Triangle::operator== (const Triangle& t) const {
	Point p1, p2, p3;
	p1 = t.get_vertex(0);
	p2 = t.get_vertex(1);
	p3 = t.get_vertex(2);
	bool f = distance(p1, p2) == distance(t.get_vertex(0), t.get_vertex(1)) && distance(p2, p3) == distance(get_vertex(1),
		get_vertex(2)) && distance(p1, p3) == distance(get_vertex(0), get_vertex(2));
	return f;
}
bool Triangle::operator!= (const Triangle& t) const {
	Point p1, p2, p3;
	p1 = t.get_vertex(0);
	p2 = t.get_vertex(1);
	p3 = t.get_vertex(2);
	bool f = distance(p1, p2) != distance(t.get_vertex(0), t.get_vertex(1)) || distance(p2, p3) != distance(t.get_vertex(1),
		t.get_vertex(2)) || distance(p1, p3) != distance(t.get_vertex(0), t.get_vertex(2));
	return f;
}

Segment middle_line(Triangle const& t, int const& k)
{
	Point p1 = t.get_vertex(0), p2 = t.get_vertex(1), p3 = t.get_vertex(2);
	Point k1, k2;
	Segment s1 = Segment(p1, p2), s2 = Segment(p2, p3), s3 = Segment(p3, p1);
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