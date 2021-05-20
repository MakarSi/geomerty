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

Point Segment::midpoint()const {
	double x = (_v1.get_x() + _v2.get_x()) / 2;
	double y = (_v1.get_y() + _v2.get_y()) / 2;
	Point p(x, y);
	return p;
}

bool intersection(const Segment& a, const Segment& b) {
	/*проверяем необходимое и достаточное условие персечения двух отрезков
	(две точки каждого из них лежат по разные стороны от прямой на которой лежит другой)*/
	Line line1(a.get_v1(), a.get_v2());
	Line line2(b.get_v1(), b.get_v2());
	int f1 = point_in_halfplane(b.get_v1(), line1);
	int g1 = point_in_halfplane(b.get_v2(), line1);
	int f2 = point_in_halfplane(a.get_v1(), line2);
	int g2 = point_in_halfplane(a.get_v2(), line2);
	if (f1 != g1 && f2 != g2 && f1 != 0 && f2 != 0)
		return true;
	else return false;
}

ostream& operator<< (ostream& out, const Segment& s) {
	out << s._v1 << ", " << s._v2;
	return out;
}

void Segment::draw()const {
	glColor3d(color.R, color.G, color.B);
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2d(_v1.get_x(), _v1.get_y());
	glVertex2d(_v2.get_x(), _v2.get_y());
	glEnd();
}