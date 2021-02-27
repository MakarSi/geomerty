#pragma once
#include "Line.h"
#include "segment.h"
#include <vector>

using namespace std;

class Polygon
{
public:
	int get_dim()const;
	void set_dim(int);
	Point get_vertex(int)const;
	void set_vertexes(vector<Point>);
	Polygon(int dim = 0, vector<Point> vertex = {});
	//���������� ��������� 
	double perimeter();
	//���������� �������
	double area();
	//����� ��������� ������ ������ � �������
	void print_coords();
private:
	//����������� ������ ��� ������������� ����� ��� ������
	int _dim;
	vector<Point> _vertex;
};