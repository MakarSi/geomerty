#define _USE_MATH_DEFINES 
#include "circle.h"

Circle::Circle(Point center, double _rad) {
	set_center(center), set_rad(_rad);
}

void Circle::set_center(Point center) {
	_center = center;
	init_ABC();
}

void Circle::set_rad(double rad) {
	if (rad <= 0) {
		cout << "Error assigning a negative or zero value to the radius " << endl;

		_rad = 1;     //В случае неправильного ввода - присваивается радиусу 1
	}
	else _rad = rad;
	init_ABC();
}

void Circle::init_ABC() {
	double x = get_center().get_x();
	double y = get_center().get_y();
	_A = -2 * x;
	_B = -2 * y;
	_C = x * x + y * y - get_rad() * get_rad();
}

Point Circle::get_center() const {
	return _center;
}

double Circle::get_rad() const {
	return _rad;
}

double Circle::get_A() const {
	return _A;
}

double Circle::get_B() const {
	return _B;
}

double Circle::get_C() const {
	return _C;
}

void Circle::print_eq(Circle const& c1) {
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

double Circle::length()const {
	return 2 * M_PI * _rad;
}

double distance(const Circle& c1, const Point& p1) {
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

Line tangent_line(const Point& p, const Circle& c){
	Line line;
	double x0 = c._center.get_x();
	double y0 = c._center.get_y();
	double x1 = p.get_x(), y1 = p.get_y();
	double r = c._rad;
	if (abs((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r) > eps)
		throw invalid_argument("Point is not on the circle");
	double A = x1 + c._A / 2;
	double B = y1 + c._B / 2;
	double C = (x1 * c._A + y1 * c._B) / 2 + c._C;
	line = { A, B, C };
	return line;
}

void tangent_lines(Point a, Circle b, Line& l1, Line& l2){
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

Segment cirlce_intersection(Circle d1, Circle d2){
	Point p1 = d1.get_center(); double r1 = d1.get_rad();
	Point p2 = d2.get_center(); double r2 = d2.get_rad();
	Point diff = p2 - p1;
	Point res1 = { INT_MAX - p1.get_x(), INT_MAX - p1.get_y() }, res2 = { INT_MAX - p1.get_x(), INT_MAX - p1.get_y() };
	double a = 2 * diff.get_x(); double b = 2 * diff.get_y(); double c = r2 * r2 - r1 * r1 - diff.get_x() * diff.get_x() - diff.get_y() * diff.get_y();
	if (a == 0 && b == 0 && c == 0)
	{
		res1 = { p1.get_x() + r1, p1.get_y() };
		res2 = { p1.get_x() - r1, p1.get_y() };
		return Segment(res1, res2);
	}
	if (b != 0)
	{
		double a1 = 1 + pow(a / b, 2);
		double b1 = 2 * a * c / (b * b);
		double c1 = pow(c / b, 2) - r1 * r1;
		double D = b1 * b1 - 4 * a1 * c1;
		if (D >= 0)
		{
			double x1 = (-b1 - sqrt(D)) / (2 * a1);
			double x2 = (-b1 + sqrt(D)) / (2 * a1);
			double y1 = -c / b - a * x1 / b;
			double y2 = -c / b - a * x2 / b;
			res1.set_x(x1); res1.set_y(y1);
			res2.set_x(x2); res2.set_y(y2);
		}
	}
	else if (a != 0)
	{
		double a1 = 1 + pow(b / a, 2);
		double b1 = 2 * b * c / (a * a);
		double c1 = pow(c / a, 2) - r1 * r1;
		double D = b1 * b1 - 4 * a1 * c1;
		if (D >= 0)
		{

			double y1 = (-b1 - sqrt(D)) / (2 * a1);
			double y2 = (-b1 + sqrt(D)) / (2 * a1);
			double x1 = -c / a - b * y1 / a;
			double x2 = -c / a - b * y2 / a;
			res1.set_x(x1); res1.set_y(y1);
			res2.set_x(x2); res2.set_y(y2);
		}
	}
	return Segment(res1 + p1, res2 + p1);
}