#pragma once
#include "Point.h"
class Vector {
public:
	void set_points(Point& p1, Point& p2);
	Point get_point1();
	Point get_point2();

	/*—оздаем вектор по двум точкам*/
	Vector(Point p1 = 0, Point p2 = 0); 
	~Vector();

	/*Ќахождение х - координаты вектора*/
	double x_coordinate_of_vector(); 
	/*Ќахождение у координаты вектора*/
	double y_coordinate_of_vector(); 
	/*Ќахождение длины вектора*/
	double length(); 
	/*Ќахождение скал€рного произведени€ 2-х векторов*/
	double scalar_product(Vector& v); 
	/*”множение вектора на число*/
	void multiplying_by_a_number(double a);
	/*Ќахождение векторного произведени€ 2-х векторов на плоскости*/
	double vector_product(Vector& v); 

	/*ѕерегрузка оператора равенства*/
	bool operator== (Vector& v);
	/*ѕерегрузка оператора неравнества*/
	bool operator!= (Vector& v);
private:
	Point _p1, _p2;
};