#pragma once
#include <vector>
#include "Line.h"
#include "segment.h"
#include "vector.h"

using namespace std;

namespace polygon{
	class Polygon: public Object
	{	
	private:
		//����������� ������ ��� ������������� ����� ��� ������
		double _area, _perimeter;
		vector<Point> _vertexes;

		//���������� ��������� 
		void init_perimeter();
		//���������� �������
		void init_area();

	public:
		Polygon(vector<Point> vertexes = {});

		//������������ ������, ������������������ ������������� ������� ����������
		void set_vertexes(vector<Point>);

		size_t get_dim()const;
		Point get_vertex(int)const;
		double get_area()const;
		double get_perimeter()const;

		friend istream& operator>> (istream&, Polygon&);
		/*bool operator== (const Polygon&);
		bool operator!= (const Polygon&);*/
		//�������� �� ������
		Polygon operator+ (const Vector& v);
		//����� ��������� ���� ������
		void print_coords(ostream&)const;
		//����� ���� ���������� � ����������������
		void print_all_info(ostream&)const;
	};
}