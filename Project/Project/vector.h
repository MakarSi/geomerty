#pragma once
#include "Point.h"
class Vector {
public:
	void set_points(Point& p1, Point& p2);
	Point get_point1();
	Point get_point2();
	Vector(Point p1 = 0, Point p2 = 0); //создаем вектор по двум точкам
	~Vector();
	double x_coordinate_of_vector(); //нахождение х координаты вектора
	double y_coordinate_of_vector(); //нахождение у координаты вектора

	void print_coordinates(); //выводит координаты вектора
	double length(); //подсчет длины вектора
	double scalar_product(Vector& v); //вычисление скалярного произведения двух векторов
	void multiplying_by_a_number(double a); //умножение вектора на число
	double vector_product(Vector& v); //вычисление векторного произведение векторов на плоскости

	bool operator== (Vector& v);//Перегрузка оператора равенства
	bool operator!= (Vector& v);//Перегрузка оператора неравнества
private:
	Point _p1, _p2;
};