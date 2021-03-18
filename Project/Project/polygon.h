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
		//установление вершин, самопересекающийся многоугольник считаем невалидным
		void set_vertexes(vector<Point>);
		//вычисление периметра 
		void set_perimeter();
		//вычисление площади
		void set_area();
		size_t get_dim()const;
		Point get_vertex(int)const;
		double get_area()const;
		double get_perimeter()const;

		friend istream& operator>> (istream&, Polygon&);
		/*bool operator== (const Polygon&);
		bool operator!= (const Polygon&);*/
		//вывод координат всех вершин
		void print_coords(ostream&);
		//вывод всей информации о четырехугольнике
		void print_all_info(ostream&);
	private:
		//многограник храним как упорядоченный набор его вершин
		double _area, _perimeter;
		vector<Point> _vertexes;
	};
}