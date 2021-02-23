#pragma once
#include "point.h"
class Triangle {
public:
	void Set_point1(Point p1);
	Point Get_point1();

	void Set_point2(Point p2);
	Point Get_point2();

	void Set_point3(Point p3);
	Point Get_point3();

	Triangle(Point p1 = 0, Point p2 = 0, Point p3 = 0); //по точкам создаем треугольник
	void Print_coordinate_of_tops();
private:
	Point _p1, _p2, _p3;
};
double Perimeter(Triangle t1);
double Square(Triangle t1);