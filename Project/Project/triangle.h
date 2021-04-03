#pragma once
#include "point.h"
#include "segment.h"
#include "polygon.h"
class Triangle : public polygon::Polygon {
public:
	//Конструктор по 3 точкам
	Triangle(vector<Point> vertexes = {});
	~Triangle();

	void set_vertexes(vector<Point>);

	/*Перегрузка оператора равенства*/
	bool operator== (const Triangle& t) const;
	/*Перегрузка оператора неравнества*/
	bool operator!= (const Triangle& t) const;

	//вспомогательные функции
	/*Средняя линия
	Для средней линии, параллельной стороне P1P2, k = 1
	Для средней линии, параллельной стороне P2P3, k = 2
	Для средней линии, параллельной стороне P1P3, k = 3*/
	friend Segment middle_line(Triangle const& t, int const& k);
};