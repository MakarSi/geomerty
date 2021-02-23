#include"triangle.h"
#include <math.h>
#include <iostream>
using namespace std;

void Triangle::Set_point1(Point p1) {
	_p1 = p1;
}
Point Triangle::Get_point1() {
	return _p1;
}

void Triangle::Set_point2(Point p2) {
	_p2 = p2;
}
Point Triangle::Get_point2() {
	return _p2;
}

void Triangle::Set_point3(Point p3) {
	_p3 = p3;
}
Point Triangle::Get_point3() {
	return _p3;
}


Triangle::Triangle(Point p1, Point p2, Point p3) {
	Set_point1(p1); Set_point2(p2); Set_point3(p3);
}

void Triangle::Print_coordinate_of_tops() {
	_p1.PrintCoordinate();
	cout << ' ';
	_p2.PrintCoordinate();
	cout << ' ';
	_p3.PrintCoordinate();
}

double Perimeter(Triangle t1) {
	return Distance(t1.Get_point1(), t1.Get_point2()) + Distance(t1.Get_point2(), t1.Get_point3())
		 + Distance(t1.Get_point1(), t1.Get_point3());
}

double Square(Triangle t1) {
	double a = Distance(t1.Get_point1(), t1.Get_point2());
	double b = Distance(t1.Get_point2(), t1.Get_point3());
	double c = Distance(t1.Get_point1(), t1.Get_point3());
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}
