#pragma once
#include <sstream>
#include <iostream>

using namespace std;

class Point
{
public:
	Point(double x = 0, double y = 0);
	double get_x()const;
	void set_x(double);
	double get_y()const;
	void set_y(double);
	void print_coordinate(); //Печатает точку
	bool operator== (const Point& a); //Перегрузка оператора равенства
	bool operator!= (const Point& a); //Перегрузка оператора неравнества
	Point operator+ (const Point& a); //Перегрузка оператора сложения
	Point operator- (const Point& a); //Перегрузка оператора вычитания
	friend istream& operator>> (istream&, Point& a); //Ввод точки
	friend ostream& operator<< (ostream&, const Point& a); //Печатает точку
	friend double distance(Point a, Point b); //Расстояние между двумя точками
protected:
	double _x, _y;
};

