#include "Line.h"
#include "Point.h"
#define _USE_MATH_DEFINES 
#include <iostream>
#include <math.h>

using namespace std;

void Line::print_equation()
{
	double a = _a, b = _b, c = _c;
	if (a > 0) cout << a << "x ";
	else if (a < 0) cout << "-" << -a << "x ";
	if (a != 0)
	{
		if (b > 0) cout << "+ " << b << "y ";
		else if (b < 0) cout << "- " << -b << "y ";
	}
	else
	{
		if (b > 0) cout << b << "y ";
		else if (b < 0) cout << "-" << -b << "y ";
	}
	if (c > 0) cout << "+ " << c << " ";
	else if (c < 0) cout << "- " << -c << " ";
	if (a == 0 && b == 0 && c == 0) cout << "0 ";
	cout << "= 0";
}

Line::Line(double a, double b, double c)
{
	if (a == 0 && b == 0)
		throw invalid_argument("This is not a line. Try to input coefficients once again.\n");
	set_a(a); set_b(b); set_c(c);
}

Line::Line(const Point& c, const Point& d)
{
	double x1 = c.get_x(), x2 = d.get_x(), y1 = c.get_y(), y2 = d.get_y();
	set_a(y1 - y2);
	set_b(x2 - x1);
	set_c(x1 * y2 - x2 * y1);
}

void Line::set_a(double a)
{
	this->_a = a;
}

void Line::set_b(double b)
{
	this->_b = b;
}

void Line::set_c(double c)
{
	this->_c = c;
}

double Line::get_a() const
{
	return _a;
}

double Line::get_b() const
{
	return _b;
}

double Line::get_c() const
{
	return _c;
}

double angle_between_lines(const Line& d, const Line& e)
{
	bool f = if_parallel(d, e);
	if (f) return 0;
	else
	{
		double res, a1 = d.get_a(), b1 = d.get_b(), a2 = e.get_a(), b2 = e.get_b();
		res = abs(float(a1 * a2 + b1 * b2)) / (sqrt(pow(a1, 2) + pow(b1, 2)) * sqrt(pow(a2, 2) + pow(b2, 2)));
		return acos(res) * 180.0 / M_PI;
	}
}

Point intersection_point(const Line& d, const Line& e)
{
	bool f = if_parallel(d, e);
	double a1 = d.get_a(), b1 = d.get_b(), c1 = d.get_c(), a2 = e.get_a(), b2 = e.get_b(), c2 = e.get_c();
	if (!f)
	{
		double det = a1 * b2 - a2 * b1, xdet = c1 * b2 - b1 * c2, ydet = a1 * c2 - a2 * c1;
		return { -(double)xdet / det,-(double)ydet / det };
	}
	else if (d == e) return { 0, c2 };
	else cout << "\nThose two lines have no intersection point\n";
	return { INT_MAX, INT_MAX };
}

bool if_parallel(const Line& d, const Line& e)
{
	double a1 = d.get_a(), b1 = d.get_b(), a2 = e.get_a(), b2 = e.get_b();
	if (a1 * b2 == b1 * a2)
	{
		if (a1 * b2 == 0)
		{
			if (a1 != 0 && a2 != 0 || b1 != 0 && b2 != 0)
				return true;
			else return false;
		}
		else return true;
	}
	else return false;
}

bool operator==(const Line& d, const Line& e)
{
	double a1 = d.get_a(), b1 = d.get_b(), c1 = d.get_c(), a2 = e.get_a(), b2 = e.get_b(), c2 = e.get_c();
	bool f = false;
	if (if_parallel(d, e))
		if (a1 * c2 == a2 * c1 || b1 * c2 == b2 * c1) f = true;
	return f;
}

istream& operator>>(istream& in, Line& d)
{
	double a, b, c;
	in >> a >> b >> c;
	if (a == 0 && b == 0)
		throw invalid_argument("This is not a line. Try to input coefficients once again.\n");
	d.set_a(a); d.set_b(b); d.set_c(c);
	return in;
}

ostream& operator<<(ostream& out, const Line& a)
{
	Line p = a;
	p.print_equation();
	return out;
}


int point_in_halfplane(const Point& e, const Line& d)
{
	double x = e.get_x(), y = e.get_y(), a = d.get_a(), b = d.get_b(), c = d.get_c();
	double sign = a * x + b * y + c;
	if (sign > 0) return 1;
	else if (sign < 0) return -1;
	if (sign == 0) return 0;
}

void Line::print_line_information()
{
	Point a, b;
	Line c, d;
	int k;
	bool f = false;
	cout << "Input two points to get a line\n";
	cin >> a >> b;
	c = Line(a, b);
	cout << "The equation of this line: " << c << endl;
	cout << "Input a point\n";
	cin >> a;
	k = point_in_halfplane(a, c);
	if (k == 1) cout << "The point belongs to the positive half-plane\n";
	else if (k == 0) cout << "The point belongs to the line\n";
	else if (k == -1) cout << "The point belongs to the negative half-plane\n";
	cout << "\nInput two more point to get another line\n";
	cin >> a >> b;
	d = Line(a, b);
	cout << "The equation of the second line: " << d << endl;
	if (if_parallel(c, d))
	{
		if (c == d) f = true;
		if (!f) cout << "These two line are parallel\n";
		else cout << "These two lines are equal\n";
	}
	else cout << "Here's the intersection point of this two lines: " << intersection_point(c, d) << endl;
	cout << "The angle between these two line is: " << angle_between_lines(c, d) << endl;
}
