#pragma once
#include "Point.h"
#include <iostream>
#include <math.h>

using namespace std;

class Line: public Object
{
public:
	Line(double a = 1, double b = 0, double c = 0);//���� ������������� ������ ���� Ax+By+C=0
	Line(const Point& a, const Point& b);//���� ������ ����� ��� �����

	friend bool operator==(const Line&, const Line&);
	friend istream& operator>> (istream&, Line&);
	friend ostream& operator<< (ostream&, const Line&);

	//���� ����� �������
	friend double angle_between_lines(const Line& a, const Line& b);
	//����� ����������� ������
	friend Point intersection_point(const Line& d, const Line& e);
	//�������� �� �������������� ���� ������
	friend bool if_parallel(const Line& d, const Line& e);
	//���� ������ ����� � ������������� �������������, �� ������� ���������� -1, ���� ����� �� ������ - 0, � ������������� ������������� - 1.
	friend int point_in_halfplane(const Point&, const Line&);

	void set_a(double a);
	void set_b(double b);
	void set_c(double c);

	double get_a() const;
	double get_b() const;
	double get_c() const;

	//�������� ��������� ������
	void print_equation();
	//�������� ��������� � ������ � �������
	static void print_line_information();

private:
	double _a, _b, _c;
};

