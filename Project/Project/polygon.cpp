#include "polygon.h"
#include "Line.h"

Polygon::Polygon(int dim, vector<Point> vertexes)
{
	set_dim(dim);
	set_vertexes(vertexes);
}

int Polygon::get_dim()const {
	return _dim;
}

void Polygon::set_dim(int dim) {
	if (dim >= 0 && dim != 1 && dim != 2)
		_dim = dim;
	else
		throw invalid_argument("Not valid dimension");
}

Point Polygon::get_vertex(int i)const {
	if (i >= 0 && i < _vertex.size())
		return _vertex[i];
	else
		throw invalid_argument("Index out of bounds");
}

void Polygon::set_vertexes(vector<Point> vertexes) {
	if (vertexes.size() < _dim)
		throw invalid_argument("Not enough vertexes");
	_vertex.clear();
	/*перед добавлением новой вершины проверяем, не является ли 
	многогранник самопересекающимся*/
	for (int i = 0; i < _dim; i++) {
		for (int j = 1; j < i - 1; j++) {
			Segment a = { vertexes[j - 1], vertexes[j] };
			Segment b = { vertexes[i - 1], vertexes[i] };
			if (intersection(a, b))
				throw invalid_argument("Intersection found");
		}
		if (i == _dim - 1) {
			for (int j = 1; j < i; j++) {
				Segment a = { vertexes[j - 1], vertexes[j] };
				Segment b = { vertexes[0], vertexes[i] };
				if (intersection(a, b))
					throw invalid_argument("Intersection found");
			}
		}
		_vertex.push_back(vertexes[i]);
	}
}

double Polygon::perimeter() {
	double res = 0;
	for (int i = 0; i < get_dim() - 1; i++)
		res += distance(get_vertex(i), get_vertex(i+1));
	res += distance(get_vertex(0), get_vertex(_dim - 1));
	return res;
}

double Polygon::area() {
	//воспользуемся формулой площади Гаусса
	double res = 0;
	if (get_dim() < 3) return 0;
	for (int i = 0; i < _dim - 1; i++) {
		res += get_vertex(i).get_x() * get_vertex(i + 1).get_y();
		res -= get_vertex(i + 1).get_x() * get_vertex(i).get_y();
	}
	res += get_vertex(get_dim() - 1).get_x() * get_vertex(0).get_y();
	res -= get_vertex(0).get_x() * get_vertex(get_dim() - 1).get_y();
	res = abs(res)/2;
	return res;
}

void Polygon::print_coords() {
	int size = get_dim();
	for (int i = 0; i < size - 1; i++)
		cout << get_vertex(i) << ", ";
	cout << get_vertex(size - 1) << endl;
}