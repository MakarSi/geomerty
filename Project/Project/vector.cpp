#include "vector.h"
void Vector::set_points(Point &p1, Point &p2) {
	_p1 = p1;
	_p2 = p2;
}
Point Vector::get_point1() {
	return _p1;
}
Point Vector::get_point2() {
	return _p2;
}
Vector::Vector(Point p1, Point p2) {
	set_points(p1, p2);
}
Vector::~Vector() {
}
double Vector::x_coordinate_of_vector() {
	return _p2.get_x() - _p1.get_x();
}
double Vector::y_coordinate_of_vector() {
	return _p2.get_y() - _p1.get_y();
}

void Vector::print_coordinates() {
	_p1.print_coordinate();
	cout << ' ';
	_p2.print_coordinate();
	cout << ' ' << endl;
}

bool Vector::operator== (Vector& v) {
	Point p1, p2;
	p1 = this->_p1;
	p2 = this->_p2;
	bool f = this->length() == v.length() && distance(p1,v._p1) == distance(p2,v._p2) && 
		distance(p1,v._p1) <= distance(p1,v._p2) && distance(p2,v._p2)<= distance(p2,v._p1);
	return f;
} 

bool Vector::operator!= (Vector& v) {
	Point p1, p2;
	p1 = this->_p1;
	p2 = this->_p2;
	bool f = this->length() == v.length() || distance(p1, v._p1) == distance(p2, v._p2) ||
		distance(p1, v._p1) <= distance(p1, v._p2) || distance(p2, v._p2) <= distance(p2, v._p1);
	return f;
}

double Vector::length() {
	return distance(_p1, _p2);
}

double Vector::scalar_product(Vector& v) {
	return this->x_coordinate_of_vector() * v.x_coordinate_of_vector() +
		this->y_coordinate_of_vector() * v.y_coordinate_of_vector();
}

void Vector::multiplying_by_a_number(double a) {
	_p2.set_x(_p2.get_x() * a);
	_p2.set_y(_p2.get_y() * a);
}

double Vector::vector_product(Vector& v) {
	return this->x_coordinate_of_vector() * v.x_coordinate_of_vector() -
		v.y_coordinate_of_vector() * this->y_coordinate_of_vector();
}