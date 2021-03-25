#include "vector.h"
Vector::Vector(Point p1, Point p2) {
	set_points(p1, p2);
}
Vector::~Vector() {
}

void Vector::set_points(Point& const p1, Point& const p2) {
	_p1 = p1;
	_p2 = p2;
}

Point Vector::get_start() const {
	return _p1;
}
Point Vector::get_finish() const {
	return _p2;
}

bool Vector::operator== (Vector& const v) {
	Point p1, p2;
	p1 = this->_p1;
	p2 = this->_p2;
	bool f = this->length() == v.length() && distance(p1, v._p1) == distance(p2, v._p2) &&
		distance(p1, v._p1) <= distance(p1, v._p2) && distance(p2, v._p2) <= distance(p2, v._p1);
	return f;
}
bool Vector::operator!= (Vector& const v) {
	Point p1, p2;
	p1 = this->_p1;
	p2 = this->_p2;
	bool f = this->length() != v.length() || distance(p1, v._p1) != distance(p2, v._p2) ||
		distance(p1, v._p1) > distance(p1, v._p2) || distance(p2, v._p2) > distance(p2, v._p1);
	return f;
}

double Vector::x_coord() {
	return _p2.get_x() - _p1.get_x();
}
double Vector::y_coord() {
	return _p2.get_y() - _p1.get_y();
}
double Vector::length() {
	return distance(_p1, _p2);
}
double Vector::scalar_product(Vector& const v) {
	return this->x_coord() * v.x_coord() +
		this->y_coord() * v.y_coord();
}
void Vector::multipl_by_num(double const &a) {
	_p2.set_x(_p2.get_x() * a);
	_p2.set_y(_p2.get_y() * a);
}
double Vector::vector_product(Vector& v) {
	return this->x_coord() * v.y_coord() - v.x_coord() * this->y_coord();
}
void Vector::print_all_info() {
	cout << "Given a vector with corodnites: (";
	cout << this->x_coord() << ", " << this->y_coord() << ')' << endl;
	cout << "Vector length: " << this->length() << endl;
	cout << "Scalar product with vector " << endl;
	cout << "Enter the coordinates of the vertices of the vector: ";
	double x3, y3, x4, y4;
	cin >> x3 >> y3 >> x4 >> y4;
	Point p3(x3, y3);
	Point p4(x4, y4);
	Vector v2(p3, p4);
	cout << endl << "Scalar product: " << this->scalar_product(v2) << endl;
	cout << "vector product with the same vector :" << this->vector_product(v2) << endl;
}