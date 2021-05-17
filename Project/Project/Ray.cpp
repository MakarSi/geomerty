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

void Ray::print_all_info() const
{
	Point p1, p2, k1, k2, k3, k4;
	cout << "Input a point to get the start of the first ray\n";
	cin >> p1;
	cout << "Input two points to get the vector for the first ray\n";
	cin >> k1 >> k2;
	Vector v1 = Vector(k1, k2);
	Ray r1 = Ray(p1, v1);
	cout << "Input a point to get the start of the second ray\n";
	cin >> p2;
	cout << "Input two points to get the vector for the second ray\n";
	cin >> k3 >> k4;
	Vector v2 = Vector(k3, k4);
	Ray r2 = Ray(p2, v2);
	bool f = intersection_point_existence(r1, r2);
	if (f)
		cout << "These two rays have the intersection point: " << ray_intersection_point(r1, r2) << endl;
	else cout << "These two rays have no intersection point\n";
	cout << "Angle between these two rays is: " << angle_between_rays(r1, r2) << endl;
}

void Ray::draw()
{	
	Vector v = _v;
	v.multipl_by_num(10000);
	Point p = _p + v;
	Segment s(_p, p);
	s.draw();
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
	double alpha = v1.scalar_product(v2) / (v1.length() * v2.length());
	return acos(alpha) * 180.0 / M_PI;
}
