#pragma once
#include <iostream>
#include "point.h"
#include "line.h"
#include "segment.h"

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

	Circle(Point center = { 0, 0 }, double _rad = 1);
	~Circle();

	/*Печать ур-ния в стандартном виде*/
	void print_eq(Circle c1);
	/*Нахождение длины окружности*/
	double length(Circle c1);
	/*Нахождение расстояние от точки до окружности*/
	double dist_circle(Circle c1, Point p1);

	/*возвращаем касательную к окружности, проходящую через точку,
	лежащую на окр-ти*/
	friend Line tangent_line(Point, Circle);
	/*находим две касательные к окружности, проходящие через точку,
	не лежащую на окр-ти, ответ храним в переданных по ссылке объектах класса Line*/
	friend void tangent_lines(Point, Circle, Line&, Line&);

	/*возвращает отрезок, концы которого - точки песечения окружностей*/
	friend Segment cirlce_intersection(Circle, Circle);

private:
	Point _center;
	double _rad;
	/*Коэффициенты А, В, С в ур-ние x^2 + y^2 + Ax + By + C = 0*/
	double _A, _B, _C;
};