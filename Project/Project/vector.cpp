#include "vector.h"

Vector::Vector(Point p1, Point p2) {
	set_x(p2.get_x() - p1.get_x());
	set_y(p2.get_y() - p1.get_y());
}

Vector::Vector(Point p) {
	set_x(p.get_x());
	set_y(p.get_y());
}

Vector::Vector(double x, double y) {
	set_x(x);
	set_y(y);
}

double Vector::length() {
	Point a = { 0, 0 };
	Point b = {_x, _y };
	return distance(a, b);
}

double Vector::scalar_product(const Vector&  v) {
	return (_x * v._x + _y * v._y);
	v._x;
}

void Vector::multipl_by_num(double a) {
	set_x(_x * a);
	set_y(_y * a);
}

double Vector::vector_product(const Vector& v) {
	return _x * v._y - v._x * _y;
}

void Vector::print_all_info() {
	cout << "Given a vector with corodnites: (";
	cout << this->_x << ", " << this->_y << ')' << endl;
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