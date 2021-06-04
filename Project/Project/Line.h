#pragma once
#include "Point.h"
#include "vector.h"
#include <iostream>
#include <math.h>

using namespace std;

class Line: public Object
{
public:
	/*Конструкторы*/
	//По коэффициентам прямой вида Ax+By+C=0
	Line(double a = 1, double b = 0, double c = 0);
	//По двум точкам
	Line(const Point& p1, const Point& p2);

	/*Сеттеры*/
	void set_abc(double, double, double);
	void set_points(const Point&, const Point&);

	/*Геттеры для коэффициентов прямой*/
	double get_a() const {return _a;}
	double get_b() const {return _b;}
	double get_c() const {return _c;}

	/*Перегрузка операторов*/
	friend bool operator==(const Line&, const Line&);
	friend istream& operator>> (istream&, Line&);
	friend ostream& operator<< (ostream&, const Line&);
	/*Сдвиг прямой на вектор*/
	Line operator+ (const Vector& v);

	//Угол между прямыми
	friend double angle_between_lines(const Line&, const Line&);
	//Точка пересечения прямых
	friend Point intersection_point(const Line&, const Line&);
	//Проверка на параллельность двух прямых
	friend bool if_parallel(const Line&, const Line&);
	//Если прямая лежит в отрицательной полуплоскости, то функция возвращает -1,
	//если лежит на прямой - 0, в положительной полуплоскости 1.
	friend int point_in_halfplane(const Point&, const Line&);
	//Прямая параллельная данной прямой, проходящая через данную точку
	friend Line parallel_line_through_point(const Line&, const Point&);
	//Получить y через x
	double y_through_x (const double&);
	//перпендикуляр через точку
	Line normal_line(const Point&)const;
	//Печатает уравнение прямой
	void print_equation()const;
	//проверяем является ли прямая неоределенной
	//p1 = {0, -INT_MAX}, p2 = {0, INT_MAX}
	bool is_undef()const { return (_p1 == Point(0, -INT_MAX) && _p2 == Point(-INT_MAX, 0)); };
	/*Принадлежит ли точка прямой*/
	bool if_belong(const Point& p) const;
	/*Рисование прямой*/
	virtual void draw()const;
	/*Печатает информацию о прямой*/
	virtual void print_info()const;
private:
	Point _p1, _p2;
	double _a, _b, _c;
};
double angle_between_lines(const Line&, const Line&);
Point intersection_point(const Line&, const Line&);
bool if_parallel(const Line&, const Line&);
int point_in_halfplane(const Point&, const Line&);
Line parallel_line_through_point(const Line&, const Point&);
