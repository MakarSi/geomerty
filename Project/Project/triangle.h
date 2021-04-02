#pragma once
#include "point.h"
#include "segment.h"
#include "polygon.h"
class Triangle: public polygon::Polygon {
public:
	//����������� �� 3 ������
	Triangle(vector<Point> vertexes = {});
	~Triangle();

	/*���������� ��������� ���������*/
	bool operator== (const Triangle& t) const;
	/*���������� ��������� �����������*/
	bool operator!= (const Triangle& t) const;

	//��������������� �������
	//������� ����� ������������
	friend Segment middle_line(Triangle const &t);

private:
	Point _p1, _p2, _p3;
};