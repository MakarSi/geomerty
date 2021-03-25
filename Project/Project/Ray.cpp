#include "Line.h"
#include "Point.h"
#define _USE_MATH_DEFINES 
#include <iostream>
#include <math.h>
#include "vector.h"
#include "Ray.h"


using namespace std;

Ray::Ray(Point p, Vector v)
{
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

Point Ray::get_point()
{
	return _p;
}

Vector Ray::get_vector()
{
	return _v;
}

bool intersectrion_point_existence(Ray r1, Ray r2)
{
	Point h1; 
	h1.set_x((r1.get_point()).get_x()); 
	h1.set_y((r1.get_point()).get_y());
	Point h2; 
	h2.set_x((r2.get_point()).get_x()); 
	h2.set_y((r2.get_point()).get_y());
	Point p1; 
	p1.set_x(h1.get_x() + (r1.get_vector()).x_coord()); 
	p1.set_y(h1.get_y() + (r1.get_vector()).y_coord());
	Point p2; 
	p2.set_x(h2.get_x() + (r2.get_vector()).x_coord()); 
	p2.set_y(h2.get_y() + (r2.get_vector()).y_coord());
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Point intr;
	Vector v1 = Vector(h1, p1), v2 = Vector(h2, p2);
	if (!if_parallel(l1, l2))
		intr = intersection_point(l1, l2);
	//else if (l1 == l2 && v1.x_coordinate_of_vector() * v2.x_coordinate_of_vector() >= 0 && v1.y_coordinate_of_vector() * v2.y_coordinate_of_vector() >= 0)
	//		return true;
	Vector v1_intr = Vector(h1, intr), v2_intr = Vector(h2, intr);
	if (v1.x_coord() * v1_intr.x_coord() >= 0 && v1.y_coord() * v1_intr.y_coord() >= 0)
		return true;
	return false;
}

Point ray_intersection_point(Ray r1, Ray r2)
{
	Point h1;
	h1.set_x((r1.get_point()).get_x());
	h1.set_y((r1.get_point()).get_y());
	Point h2;
	h2.set_x((r2.get_point()).get_x());
	h2.set_y((r2.get_point()).get_y());
	Point p1;
	p1.set_x(h1.get_x() + (r1.get_vector()).x_coord());
	p1.set_y(h1.get_y() + (r1.get_vector()).y_coord());
	Point p2;
	p2.set_x(h2.get_x() + (r2.get_vector()).x_coord());
	p2.set_y(h2.get_y() + (r2.get_vector()).y_coord());
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Point inter;
	if (intersectrion_point_existence(r1, r2))
		return intersection_point(l1, l2);
	else
	{
		cout << "These two rays don't have an intersection point\n";
		return { INT_MAX, INT_MAX };
	}
}

double angle_between_rays(Ray r1, Ray r2)
{
	Point h1;
	h1.set_x((r1.get_point()).get_x());
	h1.set_y((r1.get_point()).get_y());
	Point h2;
	h2.set_x((r2.get_point()).get_x());
	h2.set_y((r2.get_point()).get_y());
	Point p1;
	p1.set_x(h1.get_x() + (r1.get_vector()).x_coord());
	p1.set_y(h1.get_y() + (r1.get_vector()).y_coord());
	Point p2;
	p2.set_x(h2.get_x() + (r2.get_vector()).x_coord());
	p2.set_y(h2.get_y() + (r2.get_vector()).y_coord());
	Line l1 = Line(h1, p1), l2 = Line(h2, p2);
	Vector v1 = Vector(h1, p1), v2 = Vector(h2, p2);
	double alpha = v1.scalar_product(v2)/(v1.length() * v2.length());
	return acos(alpha) * 180.0 / M_PI;
}
