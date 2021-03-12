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