#pragma once
#include "Point.h"
#include <iostream>
#include <math.h>

class Ring {
public:
	Ring(Point center = 0, double _rad = 1);
	~Ring();

	void set_center(Point center);
	Point get_center();

	double get_rad();
	void set_rad(double _rad);

	/*Нахождение площади круга*/
	double square(Ring c1);
	/*Нахождение площади сегмента*/
	double sector(Ring c1, double cor);
private:
	Point _center;
	double _rad;
};