#include "Point.h"
#include <iostream>
#include <cmath>

using namespace std;

double Distance(Point a, Point b)
{
	double d1x = a.GetX();
	double d2x = b.GetX();
	double d1y = a.GetY();
	double d2y = b.GetY();
	double d = sqrt(pow(d1x - d2x, 2) + pow(d1y - d2y, 2));
	return d;
}

Point::Point(double x, double y)
{
	SetX(x); SetY(y);
}

double Point::GetX()
{
	return _x;
}

void Point::SetX(double x)
{
	_x = x;
}

double Point::GetY()
{
	return _y;
}

void Point::SetY(double y)
{
	_y = y;
}

void Point::PrintCoordinate()
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
