#pragma once
#include <iostream>
#include <math.h>
#include "Line.h"
#include "Point.h"

class Circle {
public:
	void set_center(Point center);
	Point get_center();

	double get_rad();
	void set_rad(double _rad);

	/*Устанавливаем коэффициенты ур-ния вида x^2 + y^2 + Ax + By + C = 0*/
	void set_ABC();
	double get_A();
	double get_B();
	double get_C();

	Circle(Point center, double _rad);
	~Circle();

	/*Печать ур-ния в стандартном виде*/
	void print_eq(Circle c1);
	/*Нахождение длины окружности*/
	double length(Circle c1);
	/*Возращение касательной к окружности, проходящую через точку*/
	friend Line tangent_line(Point&, Circle&);
private:
	Point _center;
	double _rad;
	/*Коэффициенты А, В, С в ур-ние x^2 + y^2 + Ax + By + C = 0*/
	double _A, _B, _C;
};