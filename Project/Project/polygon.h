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
	//вычисление периметра 
	double perimeter();
	//вычисление площади
	double area();
	//вывод координат вувсех вершин в консоль
	void print_coords();
private:
	//многограник храним как упорядоченный набор его вершин
	int _dim;
	vector<Point> _vertex;
};