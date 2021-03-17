#pragma once
#include "point.h"
class Triangle {
public:
	void set_point1(Point p1);
	Point get_point1();

	void set_point2(Point p2);
	Point get_point2();

	void set_point3(Point p3);
	Point get_point3();

	/*������� ������������ �� ���� ������*/
	Triangle(Point p1 = 0, Point p2 = 0, Point p3 = 0);
	~Triangle();

	/*������ ��������� ������ ������������*/
	void print_coordinate_of_tops();//�������� ���������� ������ ������������

	/*�������� ������������*/
	double perimeter();
	/*������� ������������*/
	double square();

	/*��� k>0 ����� ������, ����� �����*/
	void shift_right_or_left(double k);
	/*��� k>0 ����� �����, ����� ����*/
	void shift_up_or_down(double k);

	/*���������� ��������� ���������*/
	bool operator== (const Triangle& t);
	/*���������� ��������� �����������*/
	bool operator!= (const Triangle& t);
private:
	Point _p1, _p2, _p3;
};