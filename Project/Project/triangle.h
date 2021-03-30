#pragma once
#include "point.h"
#include "segment.h"
class Triangle: public Object {
public:
	//Конструктор по 3 точкам
	Triangle(Point p1 = 0, Point p2 = 0, Point p3 = 0);
	~Triangle();

	//сеттеры
	void set_point1(Point p1);
	void set_point2(Point p2);
	void set_point3(Point p3);

	//геттеры
	Point get_point1() const;
	Point get_point2() const;
	Point get_point3() const;

	/*Перегрузка оператора равенства*/
	bool operator== (const Triangle& t) const;
	/*Перегрузка оператора неравнества*/
	bool operator!= (const Triangle& t) const;

	//вспомогательные функции
	//Печать координат вершин треугольника
	void print_tops();//печатает координаты вершин треугольника
	//Периметр треугольника
	double calc_perimeter() const;
	//Площадь треугольника
	double calc_square() const;
	//сдвиг треугольника на вектор
	void shift_to_vector(double const x, double const y);
	//Средняя линия треугольника
	friend Segment middle_line(Triangle const &t);
	//вывод всей информации о треугольнике
	void print_all_info();

private:
	Point _p1, _p2, _p3;
};