#pragma once
#include "point.h"

class Circle {
public:
	void set_center(Point center);
	Point get_center();

	double get_rad();
	void set_rad(double _rad);

	Circle(Point center, double _rad);
private:
	Point _center;
	double _rad;
};

void print_equation(Circle c1);

double length_circle(Circle c1);