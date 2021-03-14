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
	if (a == 0 && b == 0 && c != 0)
		throw invalid_argument("This is not a line. Try to input coefficients once again.\n");
	set_a(a); set_b(b); set_c(c);
}

Line::Line(Point c, Point d)
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

double Line::get_a()
{
	return _a;
}

double Line::get_b()
{
	return _b;
}

double Line::get_c()
{
	return _c;
}

double angle_between_lines(Line d, Line e)
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

Point intersection_point(Line d, Line e)
{
	bool f = if_parallel(d, e);
	if (!f)
	{
		double a1 = d.get_a(), b1 = d.get_b(), c1 = d.get_c(), a2 = e.get_a(), b2 = e.get_b(), c2 = e.get_c();
		double det = a1 * b2 - a2 * b1, xdet = c1 * b2 - b1 * c2, ydet = a1 * c2 - a2 * c1;
		return { -(double)xdet / det,-(double)ydet / det };
	}
	else cout << "\nThose two lines have no intersection point\n";
	return { INT_MAX, INT_MAX };
}

bool if_parallel(Line d, Line e)
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

bool operator==(Line d, Line e)
{
	double a1 = d.get_a(), b1 = d.get_b(), c1 = d.get_c(), a2 = e.get_a(), b2 = e.get_b(), c2 = e.get_c();
	bool f = ((double)a1 / a2 == (double)b1 / b2 && (double)b1 / b2 == (double)c1 / c2);
	if (if_parallel)
	{
		if (a1 * c2 == a2 * c1 || b1 * c2 == b2 * c1) f = true;
	}
	else f = false;
	return f;
}

istream& operator>>(istream& in, Line& d)
{
	double a, b, c;
	in >> a >> b >> c;
	d.set_a(a); d.set_b(b); d.set_c(c);
	return in;
}

ostream& operator<<(ostream& out, const Line& a)
{
	Line p = a;
	p.print_equation();
	return out;
}


int point_in_halfplane(Point e, Line d)
{
	double x = e.get_x(), y = e.get_y(), a = d.get_a(), b = d.get_b(), c = d.get_c();
	double sign = a * x + b * y + c;
	if (sign > 0) return 1;
	else if (sign < 0) return -1;
	if (sign == 0) return 0;
}