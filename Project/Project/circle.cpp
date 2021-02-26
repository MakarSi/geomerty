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
		_rad = 1;     //при неправильном вводе радиуса ставится радиус равный 1
	}
	else _rad = rad;
}

double Circle::get_rad() {
	return _rad;
}

Circle::Circle(Point center = 0, double _rad = 1) {
	set_center(center), set_rad(_rad);
}

//Печать уравнение окружности
void print_equation(Circle c1) {
	Point t;
	t = c1.get_center();
	double xc = t.GetX();
	double yc = t.GetY();
	double r = c1.get_rad();
	cout << "(x";
	if (xc < 0) cout << "+" << abs(xc) << ")^2+(y";
	else if (xc > 0) cout << "-" << xc << ")^2+(y";
	if (yc < 0) cout << "+" << abs(yc) << ")^2=" << r * r;
	else if (yc > 0) cout << "-" << yc << ")^2=" << r * r;
}

//Длина окружности (дуги)
double length_circle(Circle c1) {
	double r = c1.get_rad();
	double l = 2 * 3.14 * r;
	return l;
}