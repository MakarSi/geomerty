#pragma once
#include "Point.h"
class Vector {
public:
	void set_points(Point& p1, Point& p2);
	Point get_point1();
	Point get_point2();

	/*������� ������ �� ���� ������*/
	Vector(Point p1 = 0, Point p2 = 0); 
	~Vector();

	/*���������� � - ���������� �������*/
	double x_coordinate_of_vector(); 
	/*���������� � ���������� �������*/
	double y_coordinate_of_vector(); 
	/*���������� ����� �������*/
	double length(); 
	/*���������� ���������� ������������ 2-� ��������*/
	double scalar_product(Vector& v); 
	/*��������� ������� �� �����*/
	void multiplying_by_a_number(double a);
	/*���������� ���������� ������������ 2-� �������� �� ���������*/
	double vector_product(Vector& v); 

	/*���������� ��������� ���������*/
	bool operator== (Vector& v);
	/*���������� ��������� �����������*/
	bool operator!= (Vector& v);
private:
	Point _p1, _p2;
};