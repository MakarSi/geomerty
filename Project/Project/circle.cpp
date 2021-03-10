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
		cout << "Error assigning a negative or zero value to the radius" << endl;
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

//Печать уравнения в стандартном виде
void Circle::print_eq_standart(Circle c1) {
	Point t;
	t = c1.get_center();
	double xc = t.get_x();
	double yc = t.get_y();
	double r = c1.get_rad();
	cout << "(x";
	if (xc < 0) cout << "+" << abs(xc) << ")^2+(y";
	else if (xc > 0) cout << "-" << xc << ")^2+(y";
	if (yc < 0) cout << "+" << abs(yc) << ")^2=" << r * r;
	else if (yc > 0) cout << "-" << yc << ")^2=" << r * r;
}

//Печать уравнения - скобки раскрыты
void Circle::print_eq(Circle c1) {
	Point t;
	t = c1.get_center();
	double xc = t.get_x();
	double yc = t.get_y();
	double r = c1.get_rad();
	double A = -2 * xc;
	double B = -2 * yc;
	double C = xc * xc + yc * yc - r * r;
	cout << "x^2+y^2 ";
	if (A > 0) cout << "+" << A << "x"; else cout << A << "x";
	if (B > 0) cout << "+" << B << "y"; else cout << B << "y";
	if (C > 0) cout << "+" << C << "=0"; else cout << C << "=0";
}

//Длина окружности
double Circle::length(Circle c1) {
	double r = c1.get_rad();
	double l = 2 * M_PI * r;
	return l;
}
