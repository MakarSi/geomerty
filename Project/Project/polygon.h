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
		//многограник храним как упорядоченный набор его вершин
		double _area, _perimeter;
		vector<Point> _vertexes;

		//вычисление периметра 
		void init_perimeter();
		//вычисление площади
		void init_area();

	public:
		Polygon(vector<Point> vertexes = {});

		//установление вершин, самопересекающийся многоугольник считаем невалидным
		void set_vertexes(vector<Point>);

		size_t get_dim()const;
		Point get_vertex(int)const;
		double get_area()const;
		double get_perimeter()const;

		friend istream& operator>> (istream&, Polygon&);
		/*bool operator== (const Polygon&);
		bool operator!= (const Polygon&);*/
		//смещение на вектор
		Polygon operator+ (const Vector& v);
		//вывод координат всех вершин
		void print_coords(ostream&)const;
		//вывод всей информации о четырехугольнике
		void print_all_info(ostream&)const;
	};
}