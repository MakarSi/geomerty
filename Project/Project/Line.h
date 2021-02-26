#pragma once
#include "Point.h"
#include <iostream>
#include <math.h>

using namespace std;

class Line
{
public:
	friend double angle_between_lines(Line a, Line b);//Угол между прямыми
	friend Point intersection_point(Line d, Line e);//Точка пересечения прямых
	friend bool if_parallel(Line d, Line e);//Проверка на параллельность двух прямых
	Line(double a = 0, double b = 0, double c = 0);//Ввод коэффициентов прямой вида Ax+By+C=0
	Line(Point a, Point b);//Ввод прямой через две точки
	friend bool operator==(Line d, Line e);//Перегрузка оператора равенства
	friend istream& operator>> (istream&, Line& d);
	friend ostream& operator<< (ostream&, const Line& a);
	friend int point_in_halfplane(Point a, Line d);//Если прямая лежит в отрицательной полуплоскости, то функция возвращает -1, если лежит на прямой - 0, в положительной полуплоскости - 1.
	void print_equation();//Печатает уравнение прямой
	void set_a(double a);
	void set_b(double b);
	void set_c(double c);
	double get_a();
	double get_b();
	double get_c();
private:
	double _a, _b, _c;
};

