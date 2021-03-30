#pragma once
#include "point.h"
#include "segment.h"
class Triangle: public Object {
public:
	//����������� �� 3 ������
	Triangle(Point p1 = 0, Point p2 = 0, Point p3 = 0);
	~Triangle();

	//�������
	void set_point1(Point p1);
	void set_point2(Point p2);
	void set_point3(Point p3);

	//�������
	Point get_point1() const;
	Point get_point2() const;
	Point get_point3() const;

	/*���������� ��������� ���������*/
	bool operator== (const Triangle& t) const;
	/*���������� ��������� �����������*/
	bool operator!= (const Triangle& t) const;

	//��������������� �������
	//������ ��������� ������ ������������
	void print_tops();//�������� ���������� ������ ������������
	//�������� ������������
	double calc_perimeter() const;
	//������� ������������
	double calc_square() const;
	//����� ������������ �� ������
	void shift_to_vector(double const x, double const y);
	//������� ����� ������������
	friend Segment middle_line(Triangle const &t);
	//����� ���� ���������� � ������������
	void print_all_info();

private:
	Point _p1, _p2, _p3;
};