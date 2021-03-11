#pragma once
#include "Line.h"
#include "segment.h"
#include <vector>

using namespace std;

namespace polygon {
	class Polygon
	{
	public:
		Polygon(vector<Point> vertex = {});
		//установление вершин, самопересекающийся многоугольник считаем невалидным
		void set_vertexes(vector<Point>);
		//вычисление периметра 
		void set_perimeter();
		//вычисление площади
		void set_area();
		int get_dim()const;
		Point get_vertex(int)const;
		double get_area()const;
		double get_perimeter()const;
		

		//вывод координат всех вершин в консоль
		void print_coords();
		//вывод всей информации о четырехугольнике
		void print_all_info();
	private:
		//многограник храним как упорядоченный набор его вершин
		double _area, _perimeter;
		vector<Point> _vertexes;
	};
}