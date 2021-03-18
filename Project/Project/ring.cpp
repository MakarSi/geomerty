#define _USE_MATH_DEFINES 
#include "ring.h"
#include <iostream>
#include <math.h>

using namespace std;

void Ring::set_center(Point center) {
	_center = center;
}

Point Ring::get_center() {
	return _center;
}

void Ring::set_rad(double rad) {
	if (rad <= 0) {
		_rad = 1;     //В случае неправильного ввода - присваивается радиусу 1
	}
	else _rad = rad;
}

double Ring::get_rad() {
	return _rad;
}

Ring::Ring(Point center, double _rad) {
	set_center(center), set_rad(_rad);
}

Ring::~Ring() {

}

double Ring::square(Ring c1) {
	double r = c1.get_rad();
	double l = M_PI * r * r;
	return l;
}

double Ring::sector(Ring c1, double cor) {
	double r = c1.get_rad();
	if (cor > 360) {
		while (cor > 360)
			cor -= 360;
	}
	double s = M_PI * r * r * cor / 360;
	return s;
}