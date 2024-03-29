#pragma once
#include "Point.h"
#include "vector.h"

using namespace std;

class Line: public Object
{
public:
	/*������������*/
	//�� ������������� ������ ���� Ax+By+C=0
	Line(double a = 1, double b = 0, double c = 0);
	//�� ���� ������
	Line(const Point& p1, const Point& p2);

	/*�������*/
	void set_abc(double, double, double);
	void set_points(const Point&, const Point&);

	/*������� ��� ������������� ������*/
	double get_a() const {return _a;}
	double get_b() const {return _b;}
	double get_c() const {return _c;}

	/*���������� ����������*/
	friend bool operator==(const Line&, const Line&);
	friend istream& operator>> (istream&, Line&);
	friend ostream& operator<< (ostream&, const Line&);
	/*����� ������ �� ������*/
	Line operator+ (const Vector& v);

	//���� ����� �������
	friend double angle_between_lines(const Line&, const Line&);
	//����� ����������� ������
	friend Point intersection_point(const Line&, const Line&);
	//�������� �� �������������� ���� ������
	friend bool if_parallel(const Line&, const Line&);
	//���� ������ ����� � ������������� �������������, �� ������� ���������� -1,
	//���� ����� �� ������ - 0, � ������������� ������������� 1.
	friend int point_in_halfplane(const Point&, const Line&);
	//������ ������������ ������ ������, ���������� ����� ������ �����
	friend Line parallel_line_through_point(const Line&, const Point&);
	//�������� y ����� x
	double y_through_x (const double&);
	//������������� ����� �����
	Line normal_line(const Point&)const;
	//�������� ��������� ������
	void print_equation()const;
	//��������� �������� �� ������ �������������
	//p1 = {0, -INT_MAX}, p2 = {0, INT_MAX}
	bool is_undef()const { return (_p1 == Point(0, -INT_MAX) && _p2 == Point(-INT_MAX, 0)); };
	/*����������� �� ����� ������*/
	bool if_belong(const Point& p) const;
	/*��������� ������*/
	virtual void draw()const;
	/*�������� ���������� � ������*/
	virtual void print_info()const;
private:
	Point _p1, _p2;
	double _a, _b, _c;
};
double angle_between_lines(const Line&, const Line&);
Point intersection_point(const Line&, const Line&);
bool if_parallel(const Line&, const Line&);
int point_in_halfplane(const Point&, const Line&);
Line parallel_line_through_point(const Line&, const Point&);
