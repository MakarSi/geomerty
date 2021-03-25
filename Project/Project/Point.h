#pragma once
#include <sstream>
#include <iostream>

using namespace std;

class Point
{
public:
	Point(double x = 0, double y = 0);
	double get_x()const;
	void set_x(double);
	double get_y()const;
	void set_y(double);
	void print_coordinate(); //�������� �����
	bool operator== (const Point& a); //���������� ��������� ���������
	bool operator!= (const Point& a); //���������� ��������� �����������
	Point operator+ (const Point& a); //���������� ��������� ��������
	Point operator- (const Point& a); //���������� ��������� ���������
	friend istream& operator>> (istream&, Point& a); //���� �����
	friend ostream& operator<< (ostream&, const Point& a); //�������� �����
	friend double distance(Point a, Point b); //���������� ����� ����� �������
protected:
	double _x, _y;
};

