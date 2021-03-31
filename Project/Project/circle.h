#pragma once
#include <iostream>
#include <iostream>
#include "point.h"
#include "line.h"
#include "segment.h"

class Circle: public Object {
private:
	Point _center;
	double _rad;
	double _A, _B, _C;
	void init_ABC();
public:
	/*����������� �� ����� ������ � �������*/
	Circle(Point center = { 0, 0 }, double _rad = 1);

	/*�������*/
	void set_center(Point center);
	void set_rad(double _rad);

	/*�������*/
	Point get_center() const;
	double get_rad() const;
	/*������������ ��-��� ���� x^2 + y^2 + Ax + By + C = 0*/
	double get_A() const;
	double get_B() const;
	double get_C() const;

	/*������ ��-��� � ����������� ����*/
	void print_eq();
	/*���������� ����� ����������*/
	double length()const;
	/*���������� ���������� �� ����� �� ����������
	� ������, ���� ����� ������ ���������� ���������� -1 */
	friend double distance(const Circle&, const Point&);
	/*���������� ����������� � ����������, ���������� ����� �����, ������� �� ���-��
	���� ����� �� �� ����������, ���������� ������ � �����-�� INT_MAX*/
	friend Line tangent_line(const Point&, const Circle&);
	/*������� ��� ����������� � ����������, ���������� ����� �����,
	�� ������� �� ���-��, ���� ����� ����������� �� ������ � �����-�� INT_MAX*/
	friend pair<Line, Line> tangent_lines(const Point&, const Circle&);
	/*����� ����� ����������� ���� �����������.
	���������� �������, ����� �������� - ����� �����������.
	���� ����� ����������� ���, �� ���������� �������, ���������� x � y ������ �������� ����� �������� INT_MAX*/
	friend Segment cirlce_intersection(const Circle&, const Circle&);
};