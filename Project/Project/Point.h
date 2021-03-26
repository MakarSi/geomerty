#pragma once
#include <sstream>
#include <iostream>

using namespace std;

class Point
{
public:
	Point(double x = 0, double y = 0);

	double get_x()const;
	double get_y()const;

	void set_x(double);
	void set_y(double);

	void print_coordinate(); //Печатает точку
	friend double distance(const Point&, const Point&); //Расстояние между двумя точками

	bool operator== (const Point&); //Перегрузка оператора равенства
	bool operator!= (const Point&); //Перегрузка оператора неравнества
	Point operator+ (const Point&); //Перегрузка оператора сложения
	Point operator- (const Point&); //Перегрузка оператора вычитания
	friend istream& operator>> (istream&, Point&); //Ввод точки
	friend ostream& operator<< (ostream&, const Point&); //Печатает точку

protected:
	double _x, _y;
};

