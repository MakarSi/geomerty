#pragma once
#include "Point.h"
class Vector: public Point {
public:
	//констуктор по двум точкам
	Vector(Point p1, Point p2);
	//кеонструктор по одной точке (как координаты свободного вектора)
	Vector(Point p);
	Vector(double x = 0, double y = 0);

	//сеттеры
	void set_x(double x) { _x = x; }
	void set_y(double y) { _y = y; }

	//геттеры
	double get_x() const { return _x; }
	double get_y() const { return _y; }

	/*Ќахождение длины вектора*/
	double length(); 
	/*Ќахождение скал€рного произведени€ 2-х векторов*/
	double scalar_product(const Vector&); 
	/*”множение вектора на число*/
	void multipl_by_num(double a);
	/*Ќахождение векторного произведени€ 2-х векторов на плоскости*/
	double vector_product(const Vector&); 
	void print_all_info();
};