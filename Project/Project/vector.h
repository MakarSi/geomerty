#pragma once
#include "Point.h"
class Vector {
public:
	//констуктор по двум точкам
	Vector(Point p1 = 0, Point p2 = 0); 
	~Vector();

	//сеттеры
	void set_points(Point& const p1, Point& const p2);

	//геттеры
	Point get_start() const;
	Point get_finish() const;

	/*Перегрузка оператора равенства*/
	bool operator== (Vector& const v);
	/*Перегрузка оператора неравнества*/
	bool operator!= (Vector& const v);

	/*Нахождение х - координаты вектора*/
	double x_coord(); 
	/*Нахождение у координаты вектора*/
	double y_coord(); 
	/*Нахождение длины вектора*/
	double length(); 
	/*Нахождение скалярного произведения 2-х векторов*/
	double scalar_product(Vector& const v); 
	/*Умножение вектора на число*/
	void multipl_by_num(double const &a);
	/*Нахождение векторного произведения 2-х векторов на плоскости*/
	double vector_product(Vector& const v); 
	void print_all_info();

private:
	Point _p1, _p2;
};