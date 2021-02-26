#pragma once
#include "Point.h"
#include <iostream>
#include <math.h>

using namespace std;

class Line
{
public:
	friend double angle_between_lines(Line a, Line b);//���� ����� �������
	friend Point intersection_point(Line d, Line e);//����� ����������� ������
	friend bool if_parallel(Line d, Line e);//�������� �� �������������� ���� ������
	Line(double a = 0, double b = 0, double c = 0);//���� ������������� ������ ���� Ax+By+C=0
	Line(Point a, Point b);//���� ������ ����� ��� �����
	friend bool operator==(Line d, Line e);//���������� ��������� ���������
	friend istream& operator>> (istream&, Line& d);
	friend ostream& operator<< (ostream&, const Line& a);
	friend int point_in_halfplane(Point a, Line d);//���� ������ ����� � ������������� �������������, �� ������� ���������� -1, ���� ����� �� ������ - 0, � ������������� ������������� - 1.
	void print_equation();//�������� ��������� ������
	void set_a(double a);
	void set_b(double b);
	void set_c(double c);
	double get_a();
	double get_b();
	double get_c();
private:
	double _a, _b, _c;
};

