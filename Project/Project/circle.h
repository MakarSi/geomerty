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
	//устанавливаем коэфициенты уравнения вида 
	//x^2 + y^2 + Ax + By + C = 0
	void set_ABC();
	double get_A();
	double get_B();
	double get_C();

	Circle(Point center, double _rad);
	~Circle();

	void print_eq_standart(Circle c1);
	void print_eq(Circle c1);
	double length(Circle c1);
	/*возвращаем касательную к окружности, проходящую через точку,
	лежащую на окр-ти*/
	friend Line tangent_line(Point, Circle);
	/*находим две касательные к окружности, проходящие через точку,
	не лежащую на окр-ти, ответ храним в переданных по ссылке объектах класса Line*/
	friend void tangent_lines(Point, Circle, Line&, Line&);
private:
	Point _center;
	double _rad;
	//x^2 + y^2 + Ax + By + C = 0
	double _A, _B, _C;
};