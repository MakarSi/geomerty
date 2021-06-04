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

double scalar_product(const Vector&  v1, const Vector& v2) {
	return (v1._x * v2._x + v1._y * v2._y);
}

void Vector::multipl_by_num(double a) {
	set_x(_x * a);
	set_y(_y * a);
}

double vector_product(const Vector& v1, const Vector& v2) {
	return v1._x * v2._y - v1._x * v2._y;
}

void Vector::normalize() {
	double invlength = 1 / length();
	_x *= invlength;
	_y *= invlength;
}

double determitator(const Vector& v1, const Vector& v2) {
	return (v1.get_x() * v2.get_y() - v1.get_y() * v2.get_x());
}

Vector Vector::normal_vec() {
	return Vector(-_y, _x);
}

void Vector::draw()const {
	return;
}

Vector Vector::operator*(const double& a) const
{
	Vector c;
	c._x = a * this->_x;
	c._y = a * this->_y;
	return c;
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
	cout << endl << "Scalar product: " << scalar_product(*this, v2) << endl;
	cout << "vector product with the same vector :" << vector_product(*this, v2) << endl;
}