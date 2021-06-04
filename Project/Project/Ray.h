#pragma once
#include "vector.h"
#include "Point.h"
#include "Line.h"

using namespace std;

class Ray : public Object
{
public:
	/*�����������*/
	Ray(Point p = { 0, 0 }, Vector v = {1, 0});

	/*�������*/
	void set_point(Point p) {this->_p = p;}
	void set_vector(Vector v) {this->_v = v;}

	/*�������*/
	Point get_point() const {return _p;}
	Vector get_vector() const {return _v;}

	/*����� ���� �� ������*/
	Ray operator+ (const Vector& v);
	friend istream& operator>>(istream&, Ray&);

	/*������������ �� ��� ����
	������ ��� ������������� � ������, �������� � ������ ������ ����������� ���� � ������
	�������� ���������� �� ������: https://www.interestprograms.ru/source-codes-peresechenie-lucha-i-pryamoj*/
	friend bool intersection_ray_ray(const Ray& r1, const Ray& r2);
	/*���� �� ����������� ����� ������*/
	friend bool intersection_point_existence(const Ray& r1, const Ray& r2);
	//���������� ����� ����������� �����. ���� � ���, �� ���������� ����� (INT_MAX, INT_MAX)
	friend Point ray_intersection_point(const Ray& r1, const Ray& r2);
	//���������� ���� ����� ������
	friend double angle_between_rays(const Ray& r1, const Ray& r2);
	/*���������*/
	virtual void draw()const;
	/*������ ���������� �� ���� - ������ (�����) � ������������ ������*/
	virtual void print_info()const;
private:
	Point _p; Vector _v;
};
bool intersection_ray_ray(const Ray& r1, const Ray& r2);
bool intersection_point_existence(const Ray& r1, const Ray& r2);
Point ray_intersection_point(const Ray& r1, const Ray& r2);
double angle_between_rays(const Ray& r1, const Ray& r2);