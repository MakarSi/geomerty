#pragma once
#include "Point.h"
class Vector: public Point {
public:
	//���������� �� ���� ������
	Vector(Point p1, Point p2);
	//������������ �� ����� ����� (��� ���������� ���������� �������)
	Vector(Point p);
	Vector(double x = 0, double y = 0);

	//�������
	void set_x(double x) { _x = x; }
	void set_y(double y) { _y = y; }

	//�������
	double get_x() const { return _x; }
	double get_y() const { return _y; }

	/*���������� ����� �������*/
	double length(); 
	/*���������� ���������� ������������ 2-� ��������*/
	double scalar_product(const Vector&); 
	/*��������� ������� �� �����*/
	void multipl_by_num(double a);
	/*���������� ���������� ������������ 2-� �������� �� ���������*/
	double vector_product(const Vector&); 
	void print_all_info();
};