#include "Point.h"
#include "glut/glut.h"
#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

istream& operator>>(istream& in, Point& p)
{
	double x, y;
	in >> x >> y;
	p.set_x(x); p.set_y(y);
	return in;
}

ostream& operator<<(ostream& out, const Point& p)
{
	Point a = p;
	a.print_coordinate();
	return out;
}

double distance(const Point& p1, const Point& p2)
{
	double d1x = p1.get_x();
	double d2x = p2.get_x();
	double d1y = p1.get_y();
	double d2y = p2.get_y();
	double d = sqrt((d1x - d2x)* (d1x - d2x) + (d1y - d2y) * (d1y - d2y));
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

void Point::print_coordinate()const
{
	cout << "(" << _x << "," << _y << ")";
}

bool Point::is_undef() const
{
	return (_x == INT_MAX && _y == INT_MAX);
}

bool Point::operator==(const Point& p)const
{
	bool f = this->_x == p._x && this->_y == p._y;
	return f;
}

bool Point::operator!=(const Point& p)const
{
	bool f = this->_x != p._x || this->_y != p._y;
	return f;
}

Point Point::operator+(const Point& p)const
{
	Point c;
	c._x = this->_x + p._x;
	c._y = this->_y + p._y;
	return c;
}

Point Point::operator-(const Point& p)const
{
	Point c;
	c._x = this->_x - p._x;
	c._y = this->_y - p._y;
	return c;
}

void Point::draw()const {
	glPointSize(_image._width);
	glColor3d(_image._color.R, _image._color.G, _image._color.B);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
		glVertex2d(_x, _y);
	glEnd();
}