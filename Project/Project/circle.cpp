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
		cout << "Error assigning a negative or zero value to the radius " << endl;
		_rad = 1;     //В случае неправильного ввода - присваивается радиусу 1
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
	if (dist < r) {
		cout << "This point is inside the circle" << endl;
		return -1;
	}
	return dist - r;
}

Line tangent_line(const Point& p, const Circle& c){
	Line line;
	double x0 = c._center.get_x();         //x координата центра окр-ти
	double y0 = c._center.get_y();         //y координата центра окр-ти
	double x1 = p.get_x(), y1 = p.get_y(); //x и y координаты точки 
	double r = c._rad;
	if (abs((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r) > eps)
		return line = { INT_MAX, INT_MAX, INT_MAX };
	double A = x1 + c._A / 2;
	double B = y1 + c._B / 2;
	double C = (x1 * c._A + y1 * c._B) / 2 + c._C;
	line = { A, B, C };
	return line;
}

pair<Line, Line> tangent_lines(const Point& p, const Circle& c){
	pair<Line, Line> lines;
	double x0 = c._center.get_x();
	double y0 = c._center.get_y();
	double x1 = p.get_x(), y1 = p.get_y();
	double r = c.get_rad();
	if ((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r < 0) {
		lines.first = { INT_MAX, INT_MAX, INT_MAX };
		lines.second = { INT_MAX, INT_MAX, INT_MAX };
		return lines;
	}
	/*Прямые, которые мы возвращаем имеют вид
	y = k1 (x-x1) + y1
	y = k2 (x-x1) + y1*/
	Line line1, line2;
	double k1, k2;
	if (abs(x0 - x1) == r) {
		k2 = ((y1 - y0) * (y1 - y0) - r * r) / (2 * r * (y1 - y0));
		if (x0 - x1 == r)
			k2 = -k2;
		lines.first = { 1, 0, -x1 };
		lines.second = { k2, 1, y1 - k2 * x1 };
		return lines;
	}

	k1 = (x1 - x0) * (y1 - y0) + r * sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r);
	k1 /= (x1 - x0) * (x1 - x0) - r * r;

	k2 = (x1 - x0) * (y1 - y0) - r * sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r);
	k2 /= (x1 - x0) * (x1 - x0) - r * r;

	lines.first = { -k1, 1, k1 * x1 - y1 };
	lines.second = { -k2, 1, k2 * x1 - y1};
	return lines;
}

/*если точек пересечения нет или бесконечно много возвращаем две точки с 
коорд-ми INT_MAX, если точка одна - вернем две одиниаковые точки*/
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

void Circle::print_circle_info() {
	double x1, y1, rad;
	cout << "Enter the center and radius of the circle" << endl;
	cin >> x1 >> y1 >> rad;
	Point p(x1, y1);
	Circle c(p, rad);
	cout << "Circle equation" << endl;
	c.print_eq();
	cout << "Length of the circle ";
	cout << c.length() << endl;
	cout << "Enter coordinates of point" << endl;
	cin >> x1 >> y1;
	Point p1(x1, y1);
	double dist = distance(c, p1);
	if (dist != 0) cout << "Distance from this point to the circle" << endl << dist << endl;
}