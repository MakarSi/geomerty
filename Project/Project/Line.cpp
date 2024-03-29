#define _USE_MATH_DEFINES 
#include "Line.h"

using namespace std;

Line::Line(double a, double b, double c) {
	set_abc(a, b, c);
}

Line::Line(const Point& p1, const Point& p2) {
	set_points(p1, p2);
}

void Line::set_abc(double a, double b, double c) {
	if (a == 0 && b == 0)
		throw "This is not a line. Try to input coefficients once again.";
	_a = a; 
	_b = b; 
	_c = c;
	//����� ������ �� a ��� b ����� �������� �����, ��������� ������������ ��������
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
	_p1 = p1; 
	_p2 = p2;
}

void Line::set_points(const Point& p1, const Point& p2) {
	if (p1.get_x() == p2.get_x() && p1.get_y() == p2.get_y()) {
		_a = 1; 
		_b = 0; 
		_c = 0;
		_p1 = { 0 , -INT_MAX }, 
		_p2 = { 0, INT_MAX };
	}		
	else {
		double x1 = p1.get_x(), x2 = p2.get_x(), y1 = p1.get_y(), y2 = p2.get_y();
		_a = y1 - y2;
		_b = x2 - x1;
		_c = x1 * y2 - x2 * y1;
		_p1 = p1; _p2 = p2;
	}
}

bool operator==(const Line& l1, const Line& l2) {
	double a1 = l1.get_a(), b1 = l1.get_b(), c1 = l1.get_c(), a2 = l2.get_a(), b2 = l2.get_b(), c2 = l2.get_c();
	bool f = false;
	if (if_parallel(l1, l2))
		if (a1 * c2 == a2 * c1 || b1 * c2 == b2 * c1) f = true;
	return f;
}

istream& operator>>(istream& in, Line& l) {
	double a, b, c;
	in >> a >> b >> c;
	//�������� ���������� �� ������ � ������ ��������������
	l.set_abc(a,b,c);
	return in;
}

ostream& operator<<(ostream& out, const Line& l) {
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

double angle_between_lines(const Line& l1, const Line& l2) {
	if (if_parallel(l1, l2)) return 0;
	else {
		double res, a1 = l1.get_a(), b1 = l1.get_b(), a2 = l2.get_a(), b2 = l2.get_b();
		res = abs(a1 * a2 + b1 * b2) / (sqrt(pow(a1, 2) + pow(b1, 2)) * sqrt(pow(a2, 2) + pow(b2, 2)));
		return acos(res) * 180.0 / M_PI;
	}
} 

Point intersection_point(const Line& l1, const Line& l2) {
	double a1 = l1.get_a(), b1 = l1.get_b(), c1 = l1.get_c(), a2 = l2.get_a(), b2 = l2.get_b(), c2 = l2.get_c();
	if (!if_parallel(l1, l2)) {
		double det = a1 * b2 - a2 * b1, xdet = c1 * b2 - b1 * c2, ydet = a1 * c2 - a2 * c1;
		return { -1*xdet / det,-1*ydet / det };
	}
	else if (l1 == l2) return { 0, c2 };
	return { INT_MAX, INT_MAX };
}

//���� ������ l1=l2, �� ��� ��������� �������������
bool if_parallel(const Line& l1, const Line& l2) {
	double a1 = l1.get_a(), b1 = l1.get_b(), a2 = l2.get_a(), b2 = l2.get_b();
	//������� �������������� - a1b2=a2b1
	if (a1 * b2 == b1 * a2)	{
		if (a1 * b2 == 0) {
			if (a1 != 0 && a2 != 0 || b1 != 0 && b2 != 0)
				return true;
			else return false;
		}
		else return true;
	}
	else return false;
}

int point_in_halfplane(const Point& p, const Line& l) {
	double sign = l.get_a() * p.get_x() + l.get_b() * p.get_y() + l.get_c();
	if (sign > 0) return 1;
	else if (sign < 0) return -1;
	else return 0;
}

Line parallel_line_through_point(const Line& l, const Point& p) {
	int c = -(l.get_a() * p.get_x() + l.get_b() * p.get_y());
	return Line(l.get_a(), l.get_b(), c);
}

double Line::y_through_x(const double& x) {
	//double a = this->_a, b = , c = l.get_c();
	if (_b != 0) return -(_a / _b) * x - _c / _b;
	else return 1000;
}

Line Line::normal_line(const Point& p) const {
	Line l(-_b, _a, -_a*p.get_y()+_b*p.get_x());
	return l;
}

void Line::print_equation() const {
	double a = _a, b = _b, c = _c;
	if (a > 0) cout << a << "x ";
	else if (a < 0) cout << "-" << -a << "x ";
	if (a != 0)	{
		if (b > 0) cout << "+ " << b << "y ";
		else if (b < 0) cout << "- " << -b << "y ";
	}
	else {
		if (b > 0) cout << b << "y ";
		else if (b < 0) cout << "-" << -b << "y ";
	}
	if (c > 0) cout << "+ " << c << " ";
	else if (c < 0) cout << "- " << -c << " ";
	if (a == 0 && b == 0 && c == 0) cout << "0 ";
	cout << "= 0";
}

bool Line::if_belong(const Point& p) const {
	if (_a * p.get_x() + _b * p.get_y() + _c == 0) return true; else return false;
}

void Line::draw() const {
	glColor3d(_image._color.R, _image._color.G, _image._color.B);
	glLineWidth(_image._width);
	glBegin(GL_LINES);
	Line l = *this;
	if (_b != 0) {
		glVertex2d(30000, l.y_through_x(30000));
		glVertex2d(-30000, l.y_through_x(-30000));
	}
	else {
		glVertex2d(-_c / _a, 30000);
		glVertex2d(-_c / _a, -30000);
	}
	glEnd();
}

void Line::print_info()const {
	Line l = *this;
	cout << "The line equation" << endl;
	l.print_equation();
	cout << endl;
}