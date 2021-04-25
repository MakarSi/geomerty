#pragma once
#include <vector>
#include <algorithm>
#include "Line.h"
#include "segment.h"
#include "vector.h"
#include "Ray.h"

using namespace std;

namespace polygon{
	class Polygon: public Object
	{	
	protected:
		//����������� ������ ��� ������������� ����� ��� ������
		double _area, _perimeter;
		vector<Point> _vertexes;

		//���������� ��������� 
		void init_perimeter();
		//���������� �������
		void init_area();

	public:
		Polygon(const vector<Point>& vertexes = {});

		//������������ ������, ������������������ ������������� ������� ����������
		void set_vertexes(vector<Point>);

		size_t get_dim()const { return _vertexes.size(); }
		Point get_vertex(int)const;
		double get_area()const { return _area; }
		double get_perimeter()const { return _perimeter; }

		friend istream& operator>> (istream&, Polygon&);
		/*bool operator== (const Polygon&);
		bool operator!= (const Polygon&);*/
		//�������� �� ������
		Polygon operator+ (const Vector& v);
		//���������� ����������� ����, ������������ � �������
		Ray bisector(Point);

		/*����������� ���������� ������������*/
		int rotation(Point p1, Point p2, Point p3);

		/*���������� �������� �������� �� ������
		������������ �������� �������
		�������� ����� ������� �� ������: https://algorithmica.org/ru/convex-hulls*/
		//vector<Point> convex_shell(vector<Point> points);
	};
}