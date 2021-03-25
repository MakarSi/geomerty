#pragma once
#include "point.h"
#include <iostream>
#include <math.h>

class Ring {
public:
	/*����������� �� ����� ������ � �������*/
	Ring(Point center = 0, double _rad = 1);
	~Ring();

	/*�������*/
	void set_center(Point center);
	void set_rad(double _rad);

	/*�������*/
	Point get_center() const;
	double get_rad() const;

	/*��������������� �������*/
	/*������� �����*/
	double square(Ring const& c1);
	/*������� ��������� ������� - � ������� ���������� ������ � ���� � ��������*/
	double sector(Ring const& c1, double cor);
private:
	Point _center;
	double _rad;
};