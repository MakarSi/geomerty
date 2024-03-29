#pragma once
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
	Point get_center() const {return _center;}
	double get_rad() const {return _rad;}
	/*������������ ��-��� ���� x^2 + y^2 + Ax + By + C = 0*/
	double get_A() const {return _A;}
	double get_B() const {return _B;}
	double get_C() const {return _C;}


	/*���������� ���������� ����� � ������*/
	friend istream& operator>>(istream& in, Circle& c);
	friend ostream& operator<<(ostream& out, const Circle& c);
	/*�������� ������ ���������� �� ������*/
	Circle operator+ (const Vector&);
	
	/*����������� �� ����� ����������*/
	bool if_belong(const Point& p) const;
	/*������ ��-��� � ����������� ����*/
	void print_eq()const;
	/*���������� ����� ����������*/
	double length()const;
	/*���������� ���������� �� ����� �� ����������*/
	friend double distance(const Circle& c, const Point& p);
	/*���������� ����������� � ����������, ���������� ����� �����, ������� �� ���-��
	���� ����� �� �� ����������, ���������� ������ � �����-�� INT_MAX*/
	friend Line tangent_line(const Point&, const Circle&);
	/*������� ��� ����������� � ����������, ���������� ����� �����,
	�� ������� �� ���-��, ���� ����� ����������� �� ������ � �����-�� INT_MAX*/
	friend void tangent_lines(const Point&, const Circle&, Line&, Line&);
	/*����� ����� ����������� ���� �����������.
	���������� ���� ����� �����������, ���� ����� ���� - �� ���������� ��� ����������.
	���� ����� ���������� 0 ��� ����. ����� ���������� ����� INT_MAX*/
	friend void intersection(const Circle&, const Circle&, Point&, Point&);
	/*����� ����� ����������� ������ � ����������.
	���������� ���� ����� �����������, ���� ����� ���� - �� ���������� ��� ����������.
	���� ����� ���������� 0 ���������� ����� INT_MAX*/
	friend void intersection(const Line&, const Circle&, Point&, Point&);
	/*��������� ����������*/
	virtual void draw()const;
	/*����� ���������� �� ���������� - ��������� � ����� ����*/
	virtual void print_info()const;
};
double distance(const Circle& c, const Point& p);
Line tangent_line(const Point&, const Circle&);
void tangent_lines(const Point&, const Circle&, Line&, Line&);
void intersection(const Circle&, const Circle&, Point&, Point&);
void intersection(const Line&, const Circle&, Point&, Point&);