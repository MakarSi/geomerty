#pragma once
#include "Point.h"
#include "segment.h"
#include "polygon.h"

class Triangle : public polygon::Polygon {
public:
	//Конструктор по 3 точкам
	Triangle(vector<Point> vertexes = {Point(0, 0), Point(1, 0), Point(0, 1)});
	~Triangle();

	/*Получаем набор вершин
	Если вершины 3, то создаем треугольник и проверка вынужденный он
	Если вершин больше, то берется первые 3 вершины*/
	void set_vertexes(vector<Point>);

	/*Перегрузка оператора равенства*/
	bool operator== (const Triangle& t) const;
	/*Перегрузка оператора неравнества*/
	bool operator!= (const Triangle& t) const;
	//смещение на вектор
	Triangle operator+ (const Vector& v);
	friend istream& operator>> (istream&, Triangle&);

	/*Вспомогательные функции*/
	/*Нахождение средней линии треугольника р1р2р3
	Если k=1, то средняя линия параллельная стороне р1р2
	Если k=2, то средняя линия параллельная стороне р2р3
	Если k=3, то средняя линия параллельная стороне р1р3*/
	friend Segment middle_line(const Triangle& t, int const& k);
	Segment normal(const Point&);
};