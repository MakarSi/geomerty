#pragma once
#include "Line.h"
#include "segment.h"
#include <vector>

using namespace std;

namespace polygon {
	class Polygon
	{
	public:
		Polygon(vector<Point> vertexes = {});
		//������������ ������, ������������������ ������������� ������� ����������
		void set_vertexes(vector<Point>);
		//���������� ��������� 
		void set_perimeter();
		//���������� �������
		void set_area();
		size_t get_dim()const;
		Point get_vertex(int)const;
		double get_area()const;
		double get_perimeter()const;

		friend istream& operator>> (istream&, Polygon&);
		/*bool operator== (const Polygon&);
		bool operator!= (const Polygon&);*/
		//����� ��������� ���� ������
		void print_coords(ostream&);
		//����� ���� ���������� � ����������������
		void print_all_info(ostream&);
	private:
		//����������� ������ ��� ������������� ����� ��� ������
		double _area, _perimeter;
		vector<Point> _vertexes;
	};
}