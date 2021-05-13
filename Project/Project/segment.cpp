#include "segment.h"
#include "Line.h"

Segment::Segment(Point v1, Point v2)
{
	set_v1(v1);
	set_v2(v2);
}

void Segment::set_v1(Point v1) {
	_v1 = v1;
}

void Segment::set_v2(Point v2) {
	_v2 = v2;
}

Point Segment::get_v1()const {
	return _v1;
}

Point Segment::get_v2()const {
	return _v2;
}

Segment Segment::operator+ (const Vector& v) {
	Point v1 = _v1 + v, v2 = _v2 + v;
	Segment res(v1, v2);
	return res;
}

Point Segment::midpoint(Segment const& a) {
	Point p1, p2;
	p1 = a.get_v1();
	p2 = a.get_v2();
	double x = (p1.get_x() + p2.get_x()) / 2;
	double y = (p1.get_y() + p2.get_y()) / 2;
	Point p(x, y);
	return p;
}

bool intersection(const Segment& a, const Segment& b) {
	/*проверяем необходимое и достаточное условие персечения двух отрезков
	(две точки второго из них лежат по разные стороны от прямой на которой лежит первый)*/
	Line line = { a.get_v1(), a.get_v2() };
	int f = point_in_halfplane(b.get_v1(), line);
	int g = point_in_halfplane(b.get_v2(), line);
	if (f != g && f != 0)
		return true;
	else return false;
}

void Segment::draw() {
	glColor3d(color.R, color.G, color.B);
	glBegin(GL_LINES);
	glVertex2d(_v1.get_x(), _v1.get_y());
	glVertex2d(_v2.get_x(), _v2.get_y());
	glEnd();
}