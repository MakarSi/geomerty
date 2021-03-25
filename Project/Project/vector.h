#pragma once
#include "Point.h"
class Vector {
public:
	//���������� �� ���� ������
	Vector(Point p1 = 0, Point p2 = 0); 
	~Vector();

	//�������
	void set_points(Point& const p1, Point& const p2);

	//�������
	Point get_start() const;
	Point get_finish() const;

	/*���������� ��������� ���������*/
	bool operator== (Vector& const v);
	/*���������� ��������� �����������*/
	bool operator!= (Vector& const v);

	/*���������� � - ���������� �������*/
	double x_coord(); 
	/*���������� � ���������� �������*/
	double y_coord(); 
	/*���������� ����� �������*/
	double length(); 
	/*���������� ���������� ������������ 2-� ��������*/
	double scalar_product(Vector& const v); 
	/*��������� ������� �� �����*/
	void multipl_by_num(double const &a);
	/*���������� ���������� ������������ 2-� �������� �� ���������*/
	double vector_product(Vector& const v); 
	void print_all_info();

private:
	Point _p1, _p2;
};