#pragma once
#include "Point.h"
#include "vector.h"
#include <iostream>
#include <math.h>

using namespace std;

class Line: public Object
{
public:
	Line(double a = 1, double b = 0, double c = 0);//���� ������������� ������ ���� Ax+By+C=0
	Line(const Point& p1, const Point& p2);//���� ������ ����� ��� �����

	//���� ���������� ����������� ���������� -1, ���� ���������, �� 0
	void set_abc(double, double, double);
	void set_points(const Point&, const Point&);

	double get_a() const;
	double get_b() const;
	double get_c() const;

	friend bool operator==(const Line&, const Line&);
	friend istream& operator>> (istream&, Line&);
	friend ostream& operator<< (ostream&, const Line&);
	Line operator+ (const Vector& v);

	//���� ����� �������
	friend double angle_between_lines(const Line& l1, const Line& l2);
	//����� ����������� ������
	friend Point intersection_point(const Line& l1, const Line& l2);
	//�������� �� �������������� ���� ������
	friend bool if_parallel(const Line& l1, const Line& l2);
	//���� ������ ����� � ������������� �������������, �� ������� ���������� -1, ���� ����� �� ������ - 0, � ������������� ������������� - 1.
	friend int point_in_halfplane(const Point&, const Line&);

	//�������� ��������� ������
	void print_equation();
	//�������� ��������� � ������ � �������
	static void print_line_information();

private:
	Point _p1, _p2;
	double _a, _b, _c;
};

