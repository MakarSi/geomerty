#pragma once
#include <sstream>
#include <iostream>
#include "object.h"

using namespace std;

class Point: public Object
{
public:
	Point(double x = 0, double y = 0);

	double get_x()const;
	double get_y()const;

	void set_x(double);
	void set_y(double);

	void print_coordinate()const; //�������� �����

	bool is_undef()const; //�������� �� ����� ��������������

	friend double distance(const Point&, const Point&); //���������� ����� ����� �������

	bool operator== (const Point&)const; //���������� ��������� ���������
	bool operator!= (const Point&)const; //���������� ��������� �����������
	Point operator+ (const Point&)const; //���������� ��������� ��������
	Point operator- (const Point&)const; //���������� ��������� ���������
	friend istream& operator>> (istream&, Point&); //���� �����
	friend ostream& operator<< (ostream&, const Point&); //�������� �����

	virtual void draw()const;
protected:
	double _x, _y;
};

