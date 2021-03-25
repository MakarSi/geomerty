#pragma once
#include <iostream>
#include <iostream>
#include "point.h"
#include "line.h"
#include "segment.h"

class Circle {
public:
	/*����������� �� ����� ������ � �������*/
	Circle(Point center = { 0, 0 }, double _rad = 1);
	~Circle();

	/*�������*/
	void set_center(Point center);
	void set_rad(double _rad);
	void set_ABC();

	/*�������*/
	Point get_center() const;
	double get_rad() const;
	/*������������ ������������ ��-��� ���� x^2 + y^2 + Ax + By + C = 0*/
	double get_A() const;
	double get_B() const;
	double get_C() const;

	/*��������������� �������*/
	/*������ ��-��� � ����������� ����*/
	void print_eq(Circle const& c1);
	/*���������� ����� ����������*/
	double length(Circle const& c1);
	/*���������� ���������� �� ����� �� ����������*/
	double dist_circle(Circle const& c1, Point const& p1);
	/*���������� ����������� � ����������, ���������� ����� �����, ������� �� ���-��*/
	friend Line tangent_line(Point, Circle);
	/*������� ��� ����������� � ����������, ���������� ����� �����,
	�� ������� �� ���-��, ����� ������ � ���������� �� ������ �������� ������ Line*/
	friend void tangent_lines(Point, Circle, Line&, Line&);
	/*����� ����� ����������� ���� �����������*/
	friend Segment cirlce_intersection(Circle, Circle);
private:
	Point _center;
	double _rad;
	double _A, _B, _C;
};