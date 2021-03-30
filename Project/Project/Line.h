#pragma once
#include "Point.h"
#include <iostream>
#include <math.h>

using namespace std;

class Line: public Object
{
public:
	Line(double a = 1, double b = 0, double c = 0);//Ввод коэффициентов прямой вида Ax+By+C=0
	Line(const Point& a, const Point& b);//Ввод прямой через две точки

	friend bool operator==(const Line&, const Line&);
	friend istream& operator>> (istream&, Line&);
	friend ostream& operator<< (ostream&, const Line&);

	//Угол между прямыми
	friend double angle_between_lines(const Line& a, const Line& b);
	//Точка пересечения прямых
	friend Point intersection_point(const Line& d, const Line& e);
	//Проверка на параллельность двух прямых
	friend bool if_parallel(const Line& d, const Line& e);
	//Если прямая лежит в отрицательной полуплоскости, то функция возвращает -1, если лежит на прямой - 0, в положительной полуплоскости - 1.
	friend int point_in_halfplane(const Point&, const Line&);

	void set_a(double a);
	void set_b(double b);
	void set_c(double c);

	double get_a() const;
	double get_b() const;
	double get_c() const;

	//Печатает уравнение прямой
	void print_equation();
	//Печатает инфомацию о работе с прямыми
	static void print_line_information();

private:
	double _a, _b, _c;
};

