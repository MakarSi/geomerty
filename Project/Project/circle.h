#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "line.h"
#include "segment.h"

class Circle: public Object
{
private:
	Point _center;
	double _rad;
	double _A, _B, _C;
	void init_ABC();
public:
	/*Конструктор по точке центра и радиусу*/
	Circle(Point center = { 0, 0 }, double _rad = 1);

	/*Сеттеры*/
	void set_center(Point center);
	void set_rad(double _rad);

	/*Геттеры*/
	Point get_center() const;
	double get_rad() const;
	/*коэффициенты ур-ния вида x^2 + y^2 + Ax + By + C = 0*/
	double get_A() const;
	double get_B() const;
	double get_C() const;

	/*Перегрузка операторов*/
	friend istream& operator>>(istream& in, Circle& c);
	friend ostream& operator<<(ostream& out, Circle c);
	Circle operator+ (const Vector&);
	
	/*Печать ур-ния в стандартном виде*/
	void print_eq();
	/*Нахождение длины окружности*/
	double length()const;
	/*Нахождение расстояния от точки до окружности
	В случае, если точка внутри окружности возвращает -1 */
	friend double distance(const Circle&, const Point&);
	/*Возвращает касательную к окружности, проходящую через точку, лежащую на окр-ти
	Если точка не на окружности, возвращает прямую с коорд-ми INT_MAX*/
	friend Line tangent_line(const Point&, const Circle&);
	/*Находит две касательные к окружности, проходящие через точку,
	не лежащую на окр-ти, если точка некорректна то прямые с коорд-ми INT_MAX*/
	friend void tangent_lines(const Point&, const Circle&, Line&, Line&);
	/*Поиск точек пересечения двух окружностей.
	Возвращает пару точек пересечения, если точка одна - то возвращает две одинаковые.
	Если точек пресечения 0 или беск. много возвращает точки INT_MAX*/
	friend pair<Point, Point> intersection(const Circle&, const Circle&);
	/*Поиск точек пересечения прямой и окружности.
	Возвращает пару точек пересечения, если точка одна - то возвращает две одинаковые.
	Если точек пресечения 0 возвращает точки INT_MAX*/
	friend pair<Point, Point> intersection(const Line&, const Circle&);
	virtual void draw();
};