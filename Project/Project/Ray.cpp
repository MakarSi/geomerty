#include "Line.h"
#include "Point.h"
#define _USE_MATH_DEFINES 
#include <iostream>
#include <math.h>
#include "vector.h"
#include "Ray.h"
#include "segment.h"

using namespace std;

Ray::Ray(Point p, Vector v)
{
	if (v.get_x() == 0 && v.get_y() == 0)
		throw "This vector cannot set the ray ";
	set_point(p);
	set_vector(v);
}

void Ray::set_point(Point p)
{
	this->_p = p;
}

void Ray::set_vector(Vector v)
{
	this->_v = v;
}

Point Ray::get_point() const
{
	return _p;
}

Vector Ray::get_vector() const
{
	return _v;
}

void Ray::draw()const
{	
	Vector v = _v;
	v.normalize();
	//cout << v.get_x() << " " << v.get_y() << " " << v.length()  << endl;
	v = v*10000;
	Point p = _p + v;
	glColor3d(_image._color.R, _image._color.G, _image._color.B);
	glLineWidth(_image._width);
	glBegin(GL_LINES);
	glVertex2d(_p.get_x(), _p.get_y());
	glVertex2d(p.get_x(), p.get_y());
	glEnd();
}

bool intersection_point_existence(const Ray& r1, const Ray& r2)
{
	Point h1 = { ((r1._p).get_x()), ((r1._p).get_y()) };
	Point h2 = { ((r2._p).get_x()), ((r2._p).get_y()) };
	Point p1 = { h1.get_x() + (r1._v).get_x(), h1.get_y() + (r1._v).get_y() };
	Point p2 = { h2.get_x() + (r2._v).get_x(), h2.get_y() + (r2._v).get_y() };
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Point intr;
	Vector v1 = Vector(h1, p1), v2 = Vector(h2, p2);
	if (!if_parallel(l1, l2))
		intr = intersection_point(l1, l2);
	Vector v1_intr = Vector(h1, intr), v2_intr = Vector(h2, intr);
	if (v1.get_x() * v1_intr.get_x() >= 0 && v1.get_y() * v1_intr.get_y() >= 0)
		return true;
	return false;
}

Point ray_intersection_point(const Ray& r1, const Ray& r2)
{
	Point h1 = { ((r1._p).get_x()), ((r1._p).get_y()) };
	Point h2 = { ((r2._p).get_x()), ((r2._p).get_y()) };
	Point p1 = { h1.get_x() + (r1._v).get_x(), h1.get_y() + (r1._v).get_y() };
	Point p2 = { h2.get_x() + (r2._v).get_x(), h2.get_y() + (r2._v).get_y() };
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Point inter;
	if (intersection_point_existence(r1, r2))
		return intersection_point(l1, l2);
	else
	{
		cout << "These two rays don't have an intersection point\n";
		return { INT_MAX, INT_MAX };
	}
}

double angle_between_rays(const Ray& r1, const Ray& r2)
{
	Point h1 = { ((r1._p).get_x()), ((r1._p).get_y()) };
	Point h2 = { ((r2._p).get_x()), ((r2._p).get_y()) };
	Point p1 = { h1.get_x() + (r1._v).get_x(), h1.get_y() + (r1._v).get_y() };
	Point p2 = { h2.get_x() + (r2._v).get_x(), h2.get_y() + (r2._v).get_y() };
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Vector v1 = Vector(h1, p1), v2 = Vector(h2, p2);
	double alpha = scalar_product(v1, v2) / (v1.length() * v2.length());
	return acos(alpha) * 180.0 / M_PI;
}

istream& operator>>(istream& in, Ray& r)
{
	Point p; Vector v;
	in >> p >> v;
	r = Ray(p, v);
	return in;
}

Ray Ray::operator+ (const Vector& v) {
	Point new_p = _p + v;
	Ray r(new_p, _v);
	return r;
}

void Ray::print_info()const {
	Ray r = *this;
	cout << "The begging of the ray: " << r.get_point() << endl;;
	cout << "The vector of the ray " << r.get_vector() << endl;
}