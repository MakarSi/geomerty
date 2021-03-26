#pragma once
#include <sstream>
#include <iostream>

using namespace std;

class Point
{
public:
	Point(double x = 0, double y = 0);

	double get_x()const;
	double get_y()const;

	void set_x(double);
	void set_y(double);

	void print_coordinate(); //�������� �����
	friend double distance(const Point&, const Point&); //���������� ����� ����� �������

	bool operator== (const Point&); //���������� ��������� ���������
	bool operator!= (const Point&); //���������� ��������� �����������
	Point operator+ (const Point&); //���������� ��������� ��������
	Point operator- (const Point&); //���������� ��������� ���������
	friend istream& operator>> (istream&, Point&); //���� �����
	friend ostream& operator<< (ostream&, const Point&); //�������� �����

protected:
	double _x, _y;
};

