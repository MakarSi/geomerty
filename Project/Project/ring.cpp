#define _USE_MATH_DEFINES 
#include "ring.h"

using namespace std;

Ring::Ring(Point center, double _rad) {
	set_center(center), set_rad(_rad);
}

Ring::~Ring() {

}

void Ring::set_center(Point center) {
	_center = center;
}

void Ring::set_rad(double rad) {
	if (rad <= 0) {
		cout << "Error assigning a negative or zero value to the radius " << endl;

		_rad = 1;     //В случае неправильного ввода - присваивается радиусу 1
	}
	else _rad = rad;
}

Point Ring::get_center() const {
	return _center;
}

double Ring::get_rad() const {
	return _rad;
}

double Ring::square(Ring const& c1) {
	double r = c1.get_rad();
	double l = M_PI * r * r;
	return l;
}

double Ring::sector(Ring const& c1, double cor) {
	double r = c1.get_rad();
	if (cor > 360) {
		while (cor > 360)
			cor -= 360;
	}
	double s = M_PI * r * r * cor / 360;
	return s;
}