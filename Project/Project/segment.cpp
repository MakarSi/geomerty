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