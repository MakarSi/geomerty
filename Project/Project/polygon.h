#pragma once
#include "Line.h"
#include "segment.h"
#include <vector>

using namespace std;

class Polygon
{
public:
	Polygon(vector<Point> vertex = {});
	int get_dim()const;
	Point get_vertex(int)const;
	double get_area()const;
	double get_perimeter()const;
	void set_vertexes(vector<Point>);
	//���������� ��������� 
	void set_perimeter();
	//���������� �������
	void set_area();
	//����� ��������� ���� ������ � �������
	void print_coords();
	//����� ���� ���������� � ����������������
	void print_all_info();
private:
	//����������� ������ ��� ������������� ����� ��� ������
	int _area, _perimeter;
	vector<Point> _vertexes;
};