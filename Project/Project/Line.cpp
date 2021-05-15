#include "Line.h"
#include "Point.h"
#include "vector.h"
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
	set_abc(a, b, c);
}

Line::Line(const Point& p1, const Point& p2)
{
	set_points(p1, p2);
}

void Line::set_abc(double a, double b, double c)
{
	try {
		if (a == 0 && b == 0)
			throw "This is not a line. Try to input coefficients once again.";
		_a = a; _b = b; _c = c;
		//Будем делить на a или b чтобы получить точки, проверяем корректность операции
		Point p1, p2;
		if (a == 0) {
			p1 = { 0, -c / b };
			p2 = { 1, -c / b };
		}
		if (b == 0) {
			p1 = { -c / a, 0 };
			p2 = { -c / a, 1 };
		}
		if (a != 0 && b != 0) {
			p1 = { 0, -c / b };
			p2 = { -c / a, 0 };
		}
		_p1 = p1; _p2 = p2;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		cout << "Try again"<<endl;
		cin >> a >> b >> c;
		set_abc(a, b, c);
	}
}

void Line::set_points(const Point& p1, const Point& p2) {
	if (p1.get_x() == p2.get_x() && p1.get_y() == p2.get_y()) {
		_a = 1; _b = 0; _c = 0;
		_p1 = { 0 , -INT_MAX }, _p2 = { 0, INT_MAX };
	}
	else{
		double x1 = p1.get_x(), x2 = p2.get_x(), y1 = p1.get_y(), y2 = p2.get_y();
		_a = y1 - y2;
		_b = x2 - x1;
		_c = x1 * y2 - x2 * y1;
		_p1 = p1; _p2 = p2;
	}
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

double angle_between_lines(const Line& l1, const Line& l2)
{
	bool f = if_parallel(l1, l2);
	if (f) return 0;
	else
	{
		double res, a1 = l1.get_a(), b1 = l1.get_b(), a2 = l2.get_a(), b2 = l2.get_b();
		res = abs(a1 * a2 + b1 * b2) / (sqrt(pow(a1, 2) + pow(b1, 2)) * sqrt(pow(a2, 2) + pow(b2, 2)));
		return acos(res) * 180.0 / M_PI;
	}
} 

Point intersection_point(const Line& l1, const Line& l2) 
{
	bool f = if_parallel(l1, l2);
	double a1 = l1.get_a(), b1 = l1.get_b(), c1 = l1.get_c(), a2 = l2.get_a(), b2 = l2.get_b(), c2 = l2.get_c();
	if (!f)
	{
		double det = a1 * b2 - a2 * b1, xdet = c1 * b2 - b1 * c2, ydet = a1 * c2 - a2 * c1;
		return { -1*xdet / det,-1*ydet / det };
	}
	else if (l1 == l2) return { 0, c2 };
	else cout << "\nThose two lines have no intersection point\n";
	return { INT_MAX, INT_MAX };
}

bool if_parallel(const Line& l1, const Line& l2)
{
	double a1 = l1.get_a(), b1 = l1.get_b(), a2 = l2.get_a(), b2 = l2.get_b();
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

bool operator==(const Line& l1, const Line& l2)
{
	double a1 = l1.get_a(), b1 = l1.get_b(), c1 = l1.get_c(), a2 = l2.get_a(), b2 = l2.get_b(), c2 = l2.get_c();
	bool f = false;
	if (if_parallel(l1, l2))
		if (a1 * c2 == a2 * c1 || b1 * c2 == b2 * c1) f = true;
	return f;
}

istream& operator>>(istream& in, Line& l)
{
	double a, b, c;
	in >> a >> b >> c;
	//обработка случая, когда прямая не существует в set_abc
	l.set_abc(a, b, c);
	return in;
}

ostream& operator<<(ostream& out, const Line& l)
{
	Line p = l;
	p.print_equation();
	return out;
}

Line Line::operator+ (const Vector& v) {
	Point new_p1 = _p1 + v;
	Point new_p2 = _p2 + v;
	Line l(new_p1, new_p2);
	return l;
}

int point_in_halfplane(const Point& p, const Line& l)
{
	double x = p.get_x(), y = p.get_y(), a = l.get_a(), b = l.get_b(), c = l.get_c();
	double sign = a * x + b * y + c;
	if (sign > 0) return 1;
	else if (sign < 0) return -1;
	if (sign == 0) return 0;
}

Line parallel_line_through_point(const Line& l, const Point& p)
{
	int c = -(l.get_a() * p.get_x() + l.get_b() * p.get_y());
	return Line(l.get_a(), l.get_b(), c);
}

double y_through_x(const Line& l, const double& x)
{
	double a = l.get_a(), b = l.get_b(), c = l.get_c();
	if (b != 0)
		return -(a / b) * x - c / b;
	else
		return 1000;
}

void Line::print_all_info() const
{
	cout << "Input the coefficients of the line" << endl;
	double a1, b1, c1;
	cin >> a1 >> b1 >> c1;
	Line l = Line(a1, b1, c1);
	cout << l << endl;
	Point p1, p2;
	Line l1, l2;
	int k;
	bool f = false;
	cout << "Input two points to get a line\n";
	cin >> p1 >> p2;
	l1 = Line(p1, p2);
	cout << "The equation of this line: " << l1 << endl;
	cout << "Input a point\n";
	cin >> p1;
	k = point_in_halfplane(p1, l1);
	if (k == 1) cout << "The point belongs to the positive half-plane\n";
	else if (k == 0) cout << "The point belongs to the line\n";
	else if (k == -1) cout << "The point belongs to the negative half-plane\n";
	cout << "\nInput two more point to get another line\n";
	cin >> p1 >> p2;
	l2 = Line(p1, p2);
	cout << "The equation of the second line: " << l2 << endl;
	if (if_parallel(l1, l2))
	{
		if (l1 == l2) f = true;
		if (!f) cout << "These two line are parallel\n";
		else cout << "These two lines are equal\n";
	}
	else cout << "Here's the intersection point of this two lines: " << intersection_point(l1, l2) << endl;
	cout << "The angle between these two line is: " << angle_between_lines(l1, l2) << endl;
}

void Line::draw() {
	glColor3d(color.R, color.G, color.B);
	glBegin(GL_LINES);
	glVertex2d(_p1.get_x(), _p1.get_y());
	glVertex2d(_p2.get_x(), _p2.get_y());
	glEnd();
}