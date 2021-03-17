#define _USE_MATH_DEFINES 
#include "circle.h"
#include <iostream>
#include <math.h>

using namespace std;

void Circle::set_center(Point center) {
	_center = center;
}

Point Circle::get_center() {
	return _center;
}

void Circle::set_rad(double rad) {
	if (rad <= 0) {
		cout << "Ошибка присвоения радиусу отрицательное или нулевое значение" << endl;
		_rad = 1;     //В случае неправильного ввода - присваивается радиусу 1
	}
	else _rad = rad;
}

double Circle::get_rad() {
	return _rad;
}

Circle::Circle(Point center, double _rad) {
	set_center(center), set_rad(_rad);
}

Circle::~Circle() {

}

void Circle::print_eq(Circle c1) {
	Point t;
	t = c1.get_center();
	double xc = t.get_x();
	double yc = t.get_y();
	double r = c1.get_rad();
	cout << "(x";
	if (xc < 0) cout << "+" << abs(xc) << ")^2+";
	else if (xc > 0) cout << "-" << xc << ")^2+";
	if (yc < 0) cout << "(y+" << abs(yc) << ")^2=" << r * r;
	else if (yc > 0) cout << "(y-" << yc << ")^2=" << r * r;
}

double Circle::length(Circle c1) {
	double r = c1.get_rad();
	double l = 2 * M_PI * r;
	return l;
}

void Circle::set_ABC() {
	double x = get_center().get_x();
	double y = get_center().get_y();
	_A = -2 * x;
	_B = -2 * y;
	_C = x * x + y * y - get_rad() * get_rad();
}

double Circle::get_A() {
	return _A;
}

double Circle::get_B() {
	return _B;
}

double Circle::get_C() {
	return _C;
}

Line tangent_line(Point& a, Circle& b) {
	double x0 = b.get_center().get_x();
	double y0 = b.get_center().get_y();
	double x = a.get_x(), y = a.get_y();
	if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= b.get_rad() * b.get_rad())
		throw invalid_argument("Point is not out of circle");
	double A = x0 + b.get_A() / 2;
	double B = y0 + b.get_B() / 2;
	double C = (x0 * b.get_A() + y0 * b.get_B()) / 2 + b.get_C();
	Line line = { A, B, C };
	return line;
}