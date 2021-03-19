#define _USE_MATH_DEFINES 
#include "circle.h"

using namespace std;

void Circle::set_center(Point center) {
	_center = center;
}

Point Circle::get_center() {
	return _center;
}

void Circle::set_rad(double rad) {
	if (rad <= 0) {
		cout << "Error assigning a negative or zero value to the radius " << endl;

		_rad = 1;     //В случае неправильного ввода - присваивается радиусу 1
	}
	else _rad = rad;
}

double Circle::get_rad() {
	return _rad;
}

Circle::Circle(Point center, double _rad) {
	set_center(center), set_rad(_rad);
}

Circle::~Circle() {

}

void Circle::print_eq(Circle c1) {
	Point t;
	t = c1.get_center();
	double xc = t.get_x();
	double yc = t.get_y();
	double r = c1.get_rad();
	if (xc < 0) cout << "(x+" << abs(xc) << ")^2+";
	else if (xc > 0) cout << "(x-" << xc << ")^2+";
	else if (xc == 0) cout << "x^2+";
	if (yc < 0) cout << "(y+" << abs(yc) << ")^2=" << r * r << endl;
	else if (yc > 0) cout << "(y-" << yc << ")^2=" << r * r << endl;
	else if (yc == 0) cout << "y^2=" << r * r << endl;
}

double Circle::length(Circle c1) {
	double r = c1.get_rad();
	double l = 2 * M_PI * r;
	return l;
}

double Circle::get_A() {
	return _A;
}

double Circle::get_B() {
	return _B;
}

double Circle::get_C() {
	return _C;
}

void Circle::set_ABC() {
	double x = get_center().get_x();
	double y = get_center().get_y();
	_A = -2 * x;
	_B = -2 * y;
	_C = x * x + y * y - get_rad() * get_rad();
}

double Circle::dist_circle(Circle c1, Point p1) {
	Point t;
	t = c1.get_center();
	double xc = t.get_x();
	double yc = t.get_y();
	double r = c1.get_rad();
	double dist = sqrt((xc - p1.get_x()) * (xc - p1.get_x()) + (yc - p1.get_y()) * (yc - p1.get_y()));
	if (dist == r) {
		cout << "This point belongs to a circle" << endl;
		return 0;
	}
	else if (dist < r) {
		cout << "This point is inside the circle" << endl;
		return 0;
	}
	else if (dist > r) return dist - r;
}

Line tangent_line(Point a, Circle b) {
	Line line;
	double x0 = b.get_center().get_x();
	double y0 = b.get_center().get_y();
	double x1 = a.get_x(), y1 = a.get_y();
	double r = b.get_rad();
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) != r * r)
		throw invalid_argument("Point is not on the circle");
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) == r * r) {
		double A = x1 + b.get_A() / 2;
		double B = y1 + b.get_B() / 2;
		double C = (x1 * b.get_A() + y1 * b.get_B()) / 2 + b.get_C();
		line = { A, B, C };
	}
	return line;
}

Line tangent_line(Point a, Circle b) {
	Line line;
	double x0 = b.get_center().get_x();
	double y0 = b.get_center().get_y();
	double x1 = a.get_x(), y1 = a.get_y();
	double r = b.get_rad();
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) != r * r)
		throw invalid_argument("Point is not on the circle");
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) == r * r) {
		double A = x1 + b.get_A() / 2;
		double B = y1 + b.get_B() / 2;
		double C = (x1 * b.get_A() + y1 * b.get_B()) / 2 + b.get_C();
		line = { A, B, C };
	}
	return line;
}

void tangent_lines(Point a, Circle b, Line& l1, Line& l2) {
	double x0 = b.get_center().get_x();
	double y0 = b.get_center().get_y();
	double x1 = a.get_x(), y1 = -a.get_y();
	double r = b.get_rad();
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) <= r * r)
		throw invalid_argument("Point is not on the circle");
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) > r * r) {
		//y = k1 (x-x1) + y1
		//y = k2 (x-x1) + y1
		Line line1, line2;
		double k1, k2;
		if (x0 - x1 == r) {
			k2 = -((y1 - y0) * (y1 - y0) - r * r) / (2 * r * (y1 - y0));
			l1 = { 1, 0, -x1 };
			l2 = { k2, 1, y1 - k2 * x1 };
			return;
		}
		if (x0 - x1 == -r) {
			k2 = ((y1 - y0) * (y1 - y0) - r * r) / (2 * r * (y1 - y0));
			l1 = { 1, 0, -x1 };
			l2 = { k2, 1, y1 - k2 * x1 };
			return;
		}

		k1 = (x1 - x0) * (y1 - y0) + r * sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r);
		k1 /= (x1 - x0) * (x1 - x0) - r * r;

		k2 = (x1 - x0) * (y1 - y0) - r * sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r);
		k2 /= (x1 - x0) * (x1 - x0) - r * r;
		l1 = { k1, 1, y1 - k1 * x1 };
		l2 = { k2, 1, y1 - k2 * x1 };
		return;
	}
}