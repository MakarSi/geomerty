#pragma once
#include <iostream>
#include "vector.h"
#include "Point.h"
#include "Line.h"

using namespace std;

class Ray
{
public:
	Ray(Point p = { 0, 0 }, Vector v = {});

	void set_point(Point p);
	void set_vector(Vector v);

	Point get_point() const;
	Vector get_vector() const;

	//Если существует точка пересечения между лучами возвращает true, иначе - false
	friend bool intersection_point_existence(const Ray& r1, const Ray& r2);
	//Возвращает точку пересечения лучей. Если её нет, то возвращает точку (INT_MAX, INT_MAX)
	friend Point ray_intersection_point(const Ray& r1, const Ray& r2);
	//Возвращает угол между лучами
	friend double angle_between_rays(const Ray& r1, const Ray& r2);

	//Печатает информацию о работе с лучами
	static void print_ray_information();
private:
	Point _p; Vector _v;
};

