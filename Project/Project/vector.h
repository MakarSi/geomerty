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

	/*Нахождение длины вектора*/
	double length(); 
	/*Нахождение скалярного произведения 2-х векторов*/
	friend double scalar_product(const Vector&, const Vector&);
	/*Умножение вектора на число*/
	void multipl_by_num(double a);
	/*Нахождение векторного произведения 2-х векторов на плоскости*/
	friend double vector_product(const Vector&, const Vector&);
	//Нормирование вектора
	void normalize();
	Vector normal_vec();

	Vector operator* (const double&) const;
	void print_all_info();
};