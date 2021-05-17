#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "line.h"
#include "segment.h"

class Circle: public Object
{
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

	/*���������� ����������*/
	friend istream& operator>>(istream& in, Circle& c);
	friend ostream& operator<<(ostream& out, Circle c);
	Circle operator+ (const Vector&);
	
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
	friend void tangent_lines(const Point&, const Circle&, Line&, Line&);
	/*����� ����� ����������� ���� �����������.
	���������� ���� ����� �����������, ���� ����� ���� - �� ���������� ��� ����������.
	���� ����� ���������� 0 ��� ����. ����� ���������� ����� INT_MAX*/
	friend pair<Point, Point> intersection(const Circle&, const Circle&);
	/*����� ����� ����������� ������ � ����������.
	���������� ���� ����� �����������, ���� ����� ���� - �� ���������� ��� ����������.
	���� ����� ���������� 0 ���������� ����� INT_MAX*/
	friend pair<Point, Point> intersection(const Line&, const Circle&);
	virtual void draw();
};