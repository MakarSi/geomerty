#include "Point.h"
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

istream& operator>>(istream& in, Point& a)
{
	double x, y;
	in >> x >> y;
	a.set_x(x); a.set_y(y);
	return in;
}

ostream& operator<<(ostream& out, const Point& p)
{
	Point a = p;
	a.print_coordinate();
	return out;
}

double distance(Point a, Point b)
{
	double d1x = a.get_x();
	double d2x = b.get_x();
	double d1y = a.get_y();
	double d2y = b.get_y();
	double d = sqrt(pow(d1x - d2x, 2) + pow(d1y - d2y, 2));
	return d;
}

Point::Point(double x, double y)
{
	set_x(x); set_y(y);
}

double Point::get_x()const
{
	return _x;
}

void Point::set_x(double x)
{
	_x = x;
}

double Point::get_y()const
{
	return _y;
}

void Point::set_y(double y)
{
	_y = y;
}

void Point::print_coordinate()
{
	cout << "(" << _x << "," << _y << ")";
}

bool Point::operator==(const Point& a)
{
	bool f = this->_x == a._x && this->_y == a._y;
	return f;
}

bool Point::operator!=(const Point& a)
{
	bool f = this->_x != a._x || this->_y != a._y;
	return f;
}

Point Point::operator+(const Point& a)
{
	Point c;
	c._x = this->_x + a._x;
	c._y = this->_y + a._y;
	return c;
}

Point Point::operator-(const Point& a)
{
	Point c;
	c._x = this->_x - a._x;
	c._y = this->_y - a._y;
	return c;
}