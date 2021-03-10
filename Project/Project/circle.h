#pragma once
#include "Point.h"
#include <iostream>
#include <math.h>

class Circle {
public:
	void set_center(Point center);
	Point get_center();

	double get_rad();
	void set_rad(double _rad);

	Circle(Point center, double _rad);

	void print_eq_standart(Circle c1);
	void print_eq(Circle c1);
	double length(Circle c1);
private:
	Point _center;
	double _rad;
};