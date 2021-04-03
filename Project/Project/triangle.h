#pragma once
#include "point.h"
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
	Выбор стороны, к которой будет искаться происходит внутри программы*/
	friend Segment middle_line(const Triangle& t, const int& k);
};