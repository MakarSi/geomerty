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
	Point get_point();
	void set_vector(Vector v);
	Vector get_vector();
	//���� ���������� ����� ����������� ����� ������ ���������� true, ����� - false
	friend bool intersectrion_point_existence(Ray r1, Ray r2);
	//���������� ����� ����������� �����
	friend Point ray_intersection_point(Ray r1, Ray r2);
	//���������� ���� ����� ������
	friend double angle_between_rays(Ray r1, Ray r2);
private:
	Point _p; Vector _v;
};

