#pragma once
#include "Point.h"
#include "segment.h"
#include "polygon.h"

class Triangle : public polygon::Polygon {
public:
	//Конструктор по 3 точкам
	Triangle(vector<Point> vertexes = {});
	~Triangle();

	/*Получаем набор вершин
	Если вершины 3, то создаем треугольник и проверка вынужденный он
	Если вершин больше, то берется первые 3 вершины*/
	void set_vertexes(vector<Point>);

	/*Перегрузка оператора равенства*/
	bool operator== (const Triangle& t) const;
	/*Перегрузка оператора неравнества*/
	bool operator!= (const Triangle& t) const;

	/*Вспомогательные функции*/
	/*Нахождение средней линии треугольника
	Для средней линии, параллельной стороне P1P2, k = 1
	Для средней линии, параллельной стороне P2P3, k = 2
	Для средней линии, параллельной стороне P1P3, k = 3*/
	friend Segment middle_line(const Triangle& t, int const& k);
	
};