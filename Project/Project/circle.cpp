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

void Circle::print_eq() {
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

/*если точка не лежит на окр-ти вернем неопределенную прямую*/
Line tangent_line(const Point& p, const Circle& c){
	double x0 = c._center.get_x();         //x координата центра окр-ти
	double y0 = c._center.get_y();         //y координата центра окр-ти
	double x1 = p.get_x(), y1 = p.get_y(); //x и y координаты точки 
	double r = c._rad;                     //радиус окр-ти
	if (abs((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r) > eps)
		return Line (INT_MAX, INT_MAX, INT_MAX);
	double A = x1 + c._A / 2;
	double B = y1 + c._B / 2;
	double C = (x1 * c._A + y1 * c._B) / 2 + c._C;
	return Line (A, B, C);
}

//В случае, если точка лежит внутри окружности возварщаем undef прямые
pair<Line, Line> tangent_lines(const Point& p, const Circle& c){
	pair<Line, Line> lines;
	lines.first = Line(Point(0, -INT_MAX), Point(-INT_MAX, 0));
	lines.second = Line(Point(0, -INT_MAX), Point(-INT_MAX, 0));
	Point point = p;
	Vector v1(p, c._center);
	Vector v2(p, c._center);
	double d = distance(c._center, p);
	//Если оношение радиуса на раст от точки до центра больше 1, 
	//то точка внутри окр-ти
	double angle_sin = c.get_rad()/d;
	if (angle_sin > 1)
		return lines;
	double angle_cos = sqrt(1 - angle_sin * angle_sin);
	
	//Построим вектора v1 и v2 как вектор v (вектор от точки до центра окр-ти),
	//повернутый на угол между касательными и вектором v
	double x = v1.get_x(), y = v1.get_y();
	v1.set_x(x * angle_cos - y * angle_sin);
	v1.set_y(y * angle_cos + x * angle_sin);
	lines.first = Line(p, point + v1);

	x = v2.get_x(), y = v2.get_y();
	v2.set_x(x * angle_cos + y * angle_sin);
	v2.set_y(y * angle_cos - x * angle_sin);
	lines.second = Line(p, point + v2);
	return lines;
}

/*если точек пересечения нет или бесконечно много возвращаем две точки с 
коорд-ми INT_MAX, если точка одна - вернем две одинаковые точки*/
pair<Point, Point> intersection(const Circle& c1, const Circle& c2) {
	/*проверим необходимое и достаточное условие пересечения окр-тей
	если окружности имеют общий центр - */
	if (distance(c1._center, c2._center) < abs(c2._rad - c1._rad)
		|| distance(c1._center, c2._center) > c2._rad + c1._rad 
		|| distance(c1._center, c2._center) == 0) {
		Point p1 = {INT_MAX, INT_MAX }, p2 = p1;
		pair<Point, Point> res = { p1, p2 };
		return res;
	}
	
	//получим прямую, которая проходит через точки персечения окр-тей
	double A = c1._A - c2._A;
	double B = c1._B - c2._B;
	double C = c1._C - c2._C;
	Line line = {A, B, C};
	return intersection(line, c1);
}

pair<Point, Point> intersection(const Line& l1, const Circle& c){
	Vector v { -c._center.get_x(), -c._center.get_y() };
	Line l = l1;
	l = l + v;
	double A = l.get_a();
	double B = l.get_b();
	double C = l.get_c();
	double r = c._rad;
	double x0 = -A * C / (A * A + B * B), y0 = -B * C / (A * A + B * B);
	Point p1, p2;

	if (C * C > r * r * (A * A + B * B) + eps) {
		p1 = { INT_MAX, INT_MAX }, p2 = p1;
		pair<Point, Point> res = { p1, p2 };
		return res;
	}

	else if (abs(C * C - r * r * (A * A + B * B)) < eps) {
		p1 = { x0, y0}, p2 = p1;
		pair<Point, Point> res = { p1, p2 };
		return res;
	}
	double d = r * r - C * C / (A * A + B * B);
	double mult = sqrt(d / (A * A + B * B));
	double ax, ay, bx, by;
	ax = x0 + B * mult;
	bx = x0 - B * mult;
	ay = y0 - A * mult;
	by = y0 + A* mult;
	p1 = { ax, ay }, p2 = { bx, by };
	pair<Point, Point> res = { p1, p2 };
	return res;
}

istream& operator>>(istream& in, Circle& c){
	double x, y, r;
	in >> x >> y>>r;
	Point p(x, y);
	c.set_center(p);
	c.set_rad(r);
	return in;
}

ostream& operator<<(ostream& out, Circle c){
	c.print_eq();
	return out;
}

Circle Circle::operator+ (const Vector& v) {
	Point center = _center + v;
	Circle res(center, _rad);
	return res;
}

void Circle::draw() {
	glColor3d(color.R, color.G, color.B);
	int N = 160;
	if (is_field)
		glBegin(GL_TRIANGLE_FAN);
	else
		glBegin(GL_LINE_LOOP);
	for (int i = 1; i <= N + 2; i++) {
		glVertex2f(_center.get_x() + _rad * cos(2 * 3.14 / N * i), _center.get_y() + _rad * sin(2 * 3.14 / N * i));
	}
	glEnd();
}