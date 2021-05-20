#define _USE_MATH_DEFINES 
#include "circle.h"

Circle::Circle(Point center, double _rad) {
	set_center(center);
	set_rad(_rad);
	init_ABC();
}

void Circle::set_center(Point center) {
	_center = center;
	init_ABC();
}

void Circle::set_rad(double rad) {
	if (rad <= 0) {
		throw "Radius assignment error";
	}
	else _rad = rad;
	init_ABC();
}

void Circle::init_ABC() {
	double x = _center.get_x();
	double y = _center.get_y();
	_A = -2 * x;
	_B = -2 * y;
	_C = x * x + y * y - _rad * _rad;
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

void Circle::print_eq()const {
	double xc = _center.get_x();
	double yc = _center.get_y();
	double r = _rad;
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

double distance(const Circle& c, const Point& p) {
	double xc = c._center.get_x();
	double yc = c._center.get_y();
	double r = c._rad;
	double dist = sqrt((xc - p.get_x()) * (xc - p.get_x()) + (yc - p.get_y()) * (yc - p.get_y()));
	return dist;
}

/*���� ����� �� ����� �� ���-�� ������ �������������� ������*/
Line tangent_line(const Point& p, const Circle& c){
	double x0 = c._center.get_x();         //x ���������� ������ ���-��
	double y0 = c._center.get_y();         //y ���������� ������ ���-��
	double x1 = p.get_x(), y1 = p.get_y(); //x � y ���������� ����� 
	double r = c._rad;                     //������ ���-��
	if (abs((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r) > eps)
		return Line(INT_MAX, INT_MAX, INT_MAX);
	double A = x1 + c._A / 2;
	double B = y1 + c._B / 2;
	double C = (x1 * c._A + y1 * c._B) / 2 + c._C;
	return Line(A, B, C);
}

//� ������, ���� ����� ����� ������ ���������� ���������� undef ������
void tangent_lines(const Point& p, const Circle& c, Line& l1, Line& l2){
	l1 = Line(Point(0, -INT_MAX), Point(-INT_MAX, 0));
	l2 = Line(Point(0, -INT_MAX), Point(-INT_MAX, 0));
	Point point = p;
	Vector v1(p, c._center);
	Vector v2(p, c._center);
	double d = distance(c._center, p);
	//���� �������� ������� �� ���� �� ����� �� ������ ������ 1, 
	//�� ����� ������ ���-��
	double angle_sin = c.get_rad()/d;
	if (angle_sin > 1)
		return;
	double angle_cos = sqrt(1 - angle_sin * angle_sin);
	
	//�������� ������� v1 � v2 ��� ������ v (������ �� ����� �� ������ ���-��),
	//���������� �� ���� ����� ������������ � �������� v
	double x = v1.get_x(), y = v1.get_y();
	v1.set_x(x * angle_cos - y * angle_sin);
	v1.set_y(y * angle_cos + x * angle_sin);
	l1 = Line(p, point + v1);

	x = v2.get_x(), y = v2.get_y();
	v2.set_x(x * angle_cos + y * angle_sin);
	v2.set_y(y * angle_cos - x * angle_sin);
	l2 = Line(p, point + v2);
	return;
}

/*���� ����� ����������� ��� ��� ���������� ����� ���������� ��� ����� � 
�����-�� INT_MAX, ���� ����� ���� - ������ ��� ���������� �����*/
void intersection(const Circle& c1, const Circle& c2, Point& p1, Point& p2) {
	/*�������� ����������� � ����������� ������� ����������� ���-���
	���� ���������� ����� ����� ����� - */
	if (distance(c1.get_center(), c2.get_center()) < abs(c2.get_rad() - c1.get_rad())
		|| distance(c1.get_center(), c2.get_center()) > c2.get_rad() + c1.get_rad()
		|| distance(c1.get_center(), c2.get_center()) == 0) {
		p1 = {INT_MAX, INT_MAX }, p2 = p1;
		return;
	}
	//������� ������, ������� �������� ����� ����� ���������� ���-���
	double A = c1.get_A() - c2.get_A();
	double B = c1.get_B() - c2.get_B();
	double C = c1.get_C() - c2.get_C();
	Line line = {A, B, C};
	
	intersection(line, c1, p1, p2);
}

void intersection(const Line& l1, const Circle& c, Point& p1, Point& p2){
	//������� ������������� �� ������ ���-�� �� ������
	Point p = intersection_point(l1, l1.normal_line(c.get_center()));
	//������ ������, ������������ ������ l1, ������� ��� ����� ������ 
	//��������� �� p �� ������� �����
	Vector v(c.get_center(), p);
	double d = sqrt(c.get_rad() * c.get_rad() - v.length()*v.length());
	v = v.normal_vec();
	v.multipl_by_num(d/v.length());
	//������� ����� � ��� �������, ������� �������
	p1 = p + v;
	v = Vector(-v.get_x(), -v.get_y());
	p2 = p + v;
}

istream& operator>>(istream& in, Circle& c){
	double x, y, r;
	in >> x >> y>>r;
	Point p(x, y);
	c.set_center(p);
	c.set_rad(r);
	return in;
}

ostream& operator<<(ostream& out, const Circle& c){
	c.print_eq();
	return out;
}

Circle Circle::operator+ (const Vector& v) {
	Point center = _center + v;
	Circle res(center, _rad);
	return res;
}

void Circle::draw()const {
	glColor3d(color.R, color.G, color.B);
	int N = 160;
	glLineWidth(width);
	if (is_field)
		glBegin(GL_TRIANGLE_FAN);
	else
		glBegin(GL_LINE_LOOP);
	for (int i = 1; i <= N + 2; i++) {
		glVertex2f(_center.get_x() + _rad * cos(2 * 3.14 / N * i), _center.get_y() + _rad * sin(2 * 3.14 / N * i));
	}
	glEnd();
}