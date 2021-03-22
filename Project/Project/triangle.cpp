#include"triangle.h"
#include <math.h>
#include <iostream>
using namespace std;

void Triangle::set_point1(Point p1) {
	_p1 = p1;
}

Point Triangle::get_point1() {
	return _p1;
}

void Triangle::set_point2(Point p2) {
	_p2 = p2;
}

Point Triangle::get_point2() {
	return _p2;
}

void Triangle::set_point3(Point p3) {
	_p3 = p3;
}

Point Triangle::get_point3() {
	return _p3;
}

Triangle::Triangle(Point p1, Point p2, Point p3) {
	if ((p3.get_x() - p1.get_x()) * (p2.get_y() - p1.get_y()) == (p2.get_x() - p1.get_x()) * (p3.get_y() - p1.get_y())) {
		throw "Error: A degenerate triangle!";
	}
	set_point1(p1); set_point2(p2); set_point3(p3);
}

Triangle::~Triangle() {

}

void Triangle::print_coordinate_of_tops() {
	_p1.print_coordinate();
	cout << ' ';
	_p2.print_coordinate();
	cout << ' ';
	_p3.print_coordinate();
	cout << endl;
}

double Triangle::perimeter() {
	return distance(_p1, _p2) + distance(_p2, _p3) + distance(_p1, _p3);
}

double Triangle::square() {
	double a = distance(_p1, _p2);
	double b = distance(_p2, _p3);
	double c = distance(_p1, _p3);
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

void Triangle::shift_right_or_left(double k) {
	_p1.set_x(_p1.get_x() + k);
	_p2.set_x(_p2.get_x() + k);
	_p3.set_x(_p3.get_x() + k);
}

void Triangle::shift_up_or_down(double k) {
	_p1.set_y(_p1.get_y() + k);
	_p2.set_y(_p2.get_y() + k);
	_p3.set_y(_p3.get_y() + k);
}

bool Triangle::operator== (const Triangle& t) {
	Point p1, p2, p3;
	p1 = this->get_point1();
	p2 = this->get_point2();
	p3 = this->get_point3();
	bool f = distance(p1, p2) == distance(t._p1, t._p2) && distance(p2, p3) == distance(t._p2, t._p3) && distance(p1, p3) == distance(t._p1, t._p3);
	return f;
}

bool Triangle::operator!= (const Triangle& t) {
	Point p1, p2, p3;
	p1 = this->get_point1();
	p2 = this->get_point2();
	p3 = this->get_point3();
	bool f = distance(p1, p2) != distance(t._p1, t._p2) || distance(p2, p3) != distance(t._p2, t._p3) || distance(p1, p3) != distance(t._p1, t._p3);
	return f;
}

Segment middle_line(Triangle t)
{
	int k;
	Point p1 = t.get_point1(), p2 = t.get_point2(), p3 = t.get_point3();
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
			Point k1 = s3.midpoint(s3), k2 = s2.midpoint(s2);
			return Segment(k1, k2);
		}
		else if (k == 2)
		{
			Point k1 = s1.midpoint(s1), k2 = s3.midpoint(s3);
			return Segment(k1, k2);
		}
		else if (k == 3)
		{
			Point k1 = s2.midpoint(s2), k2 = s1.midpoint(s1);
			return Segment(k1, k2);
		}
	}
	return Segment();
}