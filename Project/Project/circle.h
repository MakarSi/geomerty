#pragma once
#include <iostream>
#include <iostream>
#include "point.h"
#include "line.h"
#include "segment.h"

class Circle {
public:
	/*Конструктор по точке центра и радиусу*/
	Circle(Point center = { 0, 0 }, double _rad = 1);
	~Circle();

	/*Сеттеры*/
	void set_center(Point center);
	void set_rad(double _rad);
	void set_ABC();

	/*Геттеры*/
	Point get_center() const;
	double get_rad() const;
	/*Установление коэффициенты ур-ния вида x^2 + y^2 + Ax + By + C = 0*/
	double get_A() const;
	double get_B() const;
	double get_C() const;

	/*Вспомогательные функции*/
	/*Печать ур-ния в стандартном виде*/
	void print_eq(Circle const& c1);
	/*Нахождение длины окружности*/
	double length(Circle const& c1);
	/*Нахождение расстояния от точки до окружности*/
	double dist_circle(Circle const& c1, Point const& p1);
	/*Возвращает касательную к окружности, проходящую через точку, лежащую на окр-ти*/
	friend Line tangent_line(Point, Circle);
	/*Находит две касательные к окружности, проходящие через точку,
	не лежащую на окр-ти, ответ храним в переданных по ссылке объектах класса Line*/
	friend void tangent_lines(Point, Circle, Line&, Line&);
	/*Поиск точек пересечения двух окружностей*/
	friend Segment cirlce_intersection(Circle, Circle);
private:
	Point _center;
	double _rad;
	double _A, _B, _C;
};