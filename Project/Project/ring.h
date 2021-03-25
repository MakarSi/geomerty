#pragma once
#include "point.h"
#include <iostream>
#include <math.h>

class Ring {
public:
	/*Конструктор по точке центра и радиусу*/
	Ring(Point center = 0, double _rad = 1);
	~Ring();

	/*Сеттеры*/
	void set_center(Point center);
	void set_rad(double _rad);

	/*Геттеры*/
	Point get_center() const;
	double get_rad() const;

	/*Вспомогательные функции*/
	/*Площадь круга*/
	double square(Ring const& c1);
	/*Площадь кругового сектора - в функции передается фигура и угол в градусах*/
	double sector(Ring const& c1, double cor);
private:
	Point _center;
	double _rad;
};