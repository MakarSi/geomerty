#define _USE_MATH_DEFINES 
#include "Ray.h"

using namespace std;

Ray::Ray(Point p, Vector v){
	if (v.get_x() == 0 && v.get_y() == 0)
		throw "This vector cannot set the ray ";
	set_point(p);
	set_vector(v);
}

Ray Ray::operator+ (const Vector& v) {
	Point new_p = _p + v;
	Ray r(new_p, _v);
	return r;
}

istream& operator>>(istream& in, Ray& r) {
	Point p; Vector v;
	in >> p >> v;
	r = Ray(p, v);
	return in;
}

bool intersection_ray_ray(const Ray& r1, const Ray& r2) {
	//прямая - ray r1 - M
	Point h1 = { ((r1._p).get_x()), ((r1._p).get_y()) };
	Point p1 = { h1.get_x() + (r1._v).get_x(), h1.get_y() + (r1._v).get_y() };
	Line l1 = Line(h1, p1);
	//ray r2 _ P
	double x0, y0, v, w;
	x0 = r2._p.get_x();
	y0 = r2._p.get_y();
	Point p2 = { r2._p.get_x() + r2._v.get_x(),r2._p.get_y() + r2._v.get_y() };
	v = p2.get_x() - r2._p.get_x();
	w = p2.get_y() - r2._p.get_y();
	//line for r1
	Point p3 = r1._p + r1._v;
	double a, b, c;
	a = r1._v.get_y();
	b = (-1) * r1._v.get_x();
	c = (-1) * r1._p.get_x() * p3.get_y() + r1._p.get_y() * p3.get_x();
	double res = (-a * x0 - b * y0 - c) / (a * v + b * w);
	if (res >= 0) return true; else return false;
}

bool intersection_point_existence(const Ray& r1, const Ray& r2) {
	Line l1, l2;
	int kol = 0;
	l1 = { r1._p,r1._v + r1._p };
	l2 = { r2._p,r2._v + r2._p };
	if (r1._p == r2._p && if_parallel(l1, l2)) return true;
	else if (r1._p != r2._p && if_parallel(l1, l2)) return false;
	if (intersection_ray_ray(r1, r2)) kol++;
	if (intersection_ray_ray(r2, r1)) kol++;
	if (kol == 2) return true; return false;
}

Point ray_intersection_point(const Ray& r1, const Ray& r2) {
	Point h1 = { ((r1._p).get_x()), ((r1._p).get_y()) };
	Point h2 = { ((r2._p).get_x()), ((r2._p).get_y()) };
	Point p1 = { h1.get_x() + (r1._v).get_x(), h1.get_y() + (r1._v).get_y() };
	Point p2 = { h2.get_x() + (r2._v).get_x(), h2.get_y() + (r2._v).get_y() };
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Point inter;
	if (intersection_point_existence(r1, r2))
		return intersection_point(l1, l2);
	else return { INT_MAX, INT_MAX };
}

double angle_between_rays(const Ray& r1, const Ray& r2) {
	Point h1 = { ((r1._p).get_x()), ((r1._p).get_y()) };
	Point h2 = { ((r2._p).get_x()), ((r2._p).get_y()) };
	Point p1 = { h1.get_x() + (r1._v).get_x(), h1.get_y() + (r1._v).get_y() };
	Point p2 = { h2.get_x() + (r2._v).get_x(), h2.get_y() + (r2._v).get_y() };
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Vector v1 = Vector(h1, p1), v2 = Vector(h2, p2);
	double alpha = scalar_product(v1, v2) / (v1.length() * v2.length());
	return acos(alpha) * 180.0 / M_PI;
}

bool Ray::if_belong(const Point& p) const {
	Point p1 = _p + _v;
	Line l = Line(_p, p1);
	if (l.if_belong(p) && _p.get_x() <= p.get_x()) return true; else return false;
}

void Ray::draw() const {	
	Vector v = _v;
	v.normalize();
	v = v*100000;
	Point p = _p + v;
	glColor3d(_image._color.R, _image._color.G, _image._color.B);
	glLineWidth(_image._width);
	glBegin(GL_LINES);
	glVertex2d(_p.get_x(), _p.get_y());
	glVertex2d(p.get_x(), p.get_y());
	glEnd();
}

void Ray::print_info() const {
	Ray r = *this;
	cout << "The begging of the ray: " << r.get_point() << endl;;
	cout << "The vector of the ray " << r.get_vector() << endl;
}