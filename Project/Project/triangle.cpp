#include "triangle.h"
#include <math.h>
#include <iostream>
#include "Point.h"

using namespace std;

Triangle::Triangle(vector<Point> vertexes) {
	set_vertexes(vertexes);
	init_area();
	init_perimeter();
}

Triangle::~Triangle() {

}

void Triangle::set_vertexes(vector<Point> vertexes) {
	if (vertexes.size() != 3)
		throw "Tiangle needs 3 vertexes";
	Line l(vertexes[0], vertexes[1]);
	if (l.is_undef())
		throw "Triangle is degenerate";
	if (point_in_halfplane(vertexes[2], l) == 0)
		throw "Triangle is degenerate";
	if(vertexes[0]==vertexes[1]|| vertexes[0] == vertexes[2] || vertexes[1] == vertexes[2])
		throw "Triangle is degenerate";
	_vertexes.clear();
	for (size_t i = 0; i < vertexes.size(); i++)
		_vertexes.push_back(vertexes[i]);
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

Segment middle_line(const Triangle& t, int const& k) {
	Point p1 = t.get_vertex(0), p2 = t.get_vertex(1), p3 = t.get_vertex(2);
	Point k1, k2;
	if (k >= 1 && k <= 3) {
		if (k == 1)	{
			Segment s2 = Segment(p2, p3), s3 = Segment(p3, p1);
			k1 = s3.midpoint();
			k2 = s2.midpoint();
		}
		else if (k == 2) {
			Segment s1 = Segment(p1, p2), s3 = Segment(p3, p1);
			k1 = s1.midpoint();
			k2 = s3.midpoint();
		}
		else if (k == 3) {
			Segment s1 = Segment(p1, p2), s2 = Segment(p2, p3);
			k1 = s2.midpoint();
			k2 = s1.midpoint();
		}
		return Segment(k1, k2);
	}
	return Segment();
}

int mod(int x, int mod) {
	return x >= 0 ? x % mod : x%mod + mod;
}

Segment Triangle::normal(const Point& p) {
	int vert = -1;
	for (int i = 0; i < 3; i++) {
		if (_vertexes[i] == p)
			vert = i;
	}
	if (vert == -1) throw"Point doesnt belong to triangle";
	Vector v(_vertexes[mod(vert-1, 3)], _vertexes[mod(vert + 1, 3)]);
	Line l1(_vertexes[mod(vert - 1, 3)], _vertexes[mod(vert + 1, 3)]);
	v = v.normal_vec();
	Line l2(Point(0, 0), Point(v.get_x(), v.get_y()));
	l2 = parallel_line_through_point(l2, _vertexes[vert]);
	Segment res(_vertexes[vert], intersection_point(l1, l2));
	return res;
}

Triangle Triangle::operator+ (const Vector& v) {
	vector<Point> vertexes;
	for (int i = 0; i < get_dim(); i++)
		vertexes.push_back(_vertexes[i] + v);
	return Triangle(vertexes);
}

istream& operator>> (istream& in, Triangle& t) {
	vector<Point> vertexes;
	double x, y;
	for (int i = 0; i < 3; i++) {
		in >> x >> y;
		Point t = { x, y };
		vertexes.push_back(t);
	}
	t = vertexes;
	return in;
}