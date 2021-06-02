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
		//многограник храним как упорядоченный набор его вершин
		double _area, _perimeter;
		vector<Point> _vertexes;

		//вычисление периметра 
		void init_perimeter();
		//вычисление площади
		void init_area();
	public:
		Polygon(const vector<Point>& vertexes = 
			{Point(0, 0), Point(0, 1), Point(1,1), Point(1, 0)});
		virtual void draw()const;

		//установление вершин, самопересекающийся многоугольник считаем невалидным
		void set_vertexes(vector<Point>);

		size_t get_dim()const { return _vertexes.size(); }
		Point get_vertex(int)const;
		double get_area()const { return _area; }
		double get_perimeter()const { return _perimeter; }

		Polygon& operator= (const Polygon& poly);
		
		friend istream& operator>> (istream&, Polygon&);
		/*bool operator== (const Polygon&);
		bool operator!= (const Polygon&);*/
		//смещение на вектор
		Polygon operator+ (const Vector& v);
		//нахождение биссектрисы угла, относящегося к вершине
		Ray bisector(Point)const;

		/*Определение ориентации треугольника
		Вывод: 1 - положительная ориентация, -1 - отрицательная ориентация треугольника, иначе 0*/
		friend double rotation(const Point& p1, const Point& p2, const Point& p3);

		/*Построение выпуклой оболочки по точкам
		Используется алгоритм Грэхема
		Подробно можно изучить по ссылке: https://algorithmica.org/ru/convex-hulls*/
		friend Polygon convex_shell(vector<Point> points);
		/*Компаратор для сортировки точек по полярному углу*/
		friend bool cop(const Point& p1, const Point& p2);
	};
	Polygon convex_shell(vector<Point> points);
	double rotation(const Point& p1, const Point& p2, const Point& p3);
	bool cop(const Point& p1, const Point& p2);
}