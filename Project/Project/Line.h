#pragma once
#include "Point.h"
#include "vector.h"
#include <iostream>
#include <math.h>

using namespace std;

class Line: public Object
{
public:
	Line(double a = 1, double b = 0, double c = 0);//Ввод коэффициентов прямой вида Ax+By+C=0
	Line(const Point& p1, const Point& p2);//Ввод прямой через две точки

	//если отработало некорректно возвращает -1, если корректно, то 0
	void set_abc(double, double, double);
	void set_points(const Point&, const Point&);

	double get_a() const;
	double get_b() const;
	double get_c() const;

	friend bool operator==(const Line&, const Line&);
	friend istream& operator>> (istream&, Line&);
	friend ostream& operator<< (ostream&, const Line&);
	Line operator+ (const Vector& v);

	//Угол между прямыми
	friend double angle_between_lines(const Line& l1, const Line& l2);
	//Точка пересечения прямых
	friend Point intersection_point(const Line& l1, const Line& l2);
	//Проверка на параллельность двух прямых
	friend bool if_parallel(const Line& l1, const Line& l2);
	//Если прямая лежит в отрицательной полуплоскости, то функция возвращает -1,
	//если лежит на прямой - 0, в положительной полуплоскости - 1.
	friend int point_in_halfplane(const Point&, const Line&);
	//Прямая параллельная данной прямой, проходящая через данную точку
	friend Line parallel_line_through_point(const Line&, const Point&);
	//Получить y через x
	friend double y_through_x(const Line&, const double&);

	//Печатает уравнение прямой
	void print_equation();
	//Печатает инфомацию о работе с прямыми
	void print_all_info() const;
	//проверяем является ли прямая неоределенной
	//p1 = {0, -INT_MAX}, p2 = {0, INT_MAX}
	bool is_undef()const { return (_p1 == Point(0, -INT_MAX) && _p2 == Point(-INT_MAX, 0)); };
	virtual void draw();
private:
	Point _p1, _p2;
	double _a, _b, _c;
};

