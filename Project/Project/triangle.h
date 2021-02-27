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

	Triangle(Point p1 = 0, Point p2 = 0, Point p3 = 0);//по точкам создаем треугольник
	void print_coordinate_of_tops();//печатает координаты вершин треугольника

	double perimeter();//находит периметр треугольника
	double square();//находит площадь треугольника

	void shift_right_or_left(double k);//при k>0 сдвиг вправо, иначе влево
	void shift_up_or_down(double k);//при k>0 сдвиг вверх, иначе вниз

	bool operator== (const Triangle& t);//Перегрузка оператора равенства
	bool operator!= (const Triangle& t);//Перегрузка оператора неравнества
private:
	Point _p1, _p2, _p3;
};