#pragma once
#include "point.h"
class Triangle {
public:
	void set_point1(Point p1);
	Point get_point1();

	void set_point2(Point p2);
	Point get_point2();

	void set_point3(Point p3);
	Point get_point3();

	/*Задание треугольника по трем точкам*/
	Triangle(Point p1 = 0, Point p2 = 0, Point p3 = 0);
	~Triangle();

	/*Печать координат вершин треугольника*/
	void print_coordinate_of_tops();//печатает координаты вершин треугольника

	/*Периметр треугольника*/
	double perimeter();
	/*Площадь треугольника*/
	double square();

	/*При k>0 сдвиг вправо, иначе влево*/
	void shift_right_or_left(double k);
	/*При k>0 сдвиг вверх, иначе вниз*/
	void shift_up_or_down(double k);

	/*Перегрузка оператора равенства*/
	bool operator== (const Triangle& t);
	/*Перегрузка оператора неравнества*/
	bool operator!= (const Triangle& t);
private:
	Point _p1, _p2, _p3;
};