#include "polygon.h"
#include "Line.h"

Polygon::Polygon(vector<Point> vertexes)
{
	set_vertexes(vertexes);
	set_area();
	set_perimeter();
}


Point Polygon::get_vertex(int i)const {
	if (i >= 0 && i < _vertexes.size())
		return _vertexes[i];
	else
		throw invalid_argument("Index out of bounds");
}

int Polygon::get_dim()const{
	return _vertexes.size();
}

double Polygon::get_area()const {
	return _area;
}

double Polygon::get_perimeter()const {
	return _perimeter;
}

void Polygon::set_vertexes(vector<Point> vertexes) {
	if (vertexes.size() < 3)
		throw invalid_argument("Not enough vertexes");
	/*перед добавлением новой вершины проверяем, не является ли 
	многогранник самопересекающимся*/
	for (int i = 0; i < get_dim(); i++) {
		for (int j = 1; j < i - 1; j++) {
			Segment a = { vertexes[j - 1], vertexes[j] };
			Segment b = { vertexes[i - 1], vertexes[i] };
			if (intersection(a, b))
				throw invalid_argument("Intersection found");
		}
		if (i == get_dim() - 1) {
			for (int j = 1; j < i; j++) {
				Segment a = { vertexes[j - 1], vertexes[j] };
				Segment b = { vertexes[0], vertexes[i] };
				if (intersection(a, b))
					throw invalid_argument("Intersection found");
			}
		}
		_vertexes.push_back(vertexes[i]);
	}
}

void Polygon::set_perimeter() {
	double res = 0;
	for (int i = 0; i < get_dim() - 1; i++)
		res += distance(get_vertex(i), get_vertex(i+1));
	res += distance(get_vertex(0), get_vertex(get_dim() - 1));
	_perimeter = res;
}

void Polygon::set_area() {
	//воспользуемся формулой площади Гаусса
	double res = 0;
	if (get_dim() < 3) {
		_area = 0;
		return;
	}
	for (int i = 0; i < get_dim() - 1; i++) {
		res += get_vertex(i).get_x() * get_vertex(i + 1).get_y();
		res -= get_vertex(i + 1).get_x() * get_vertex(i).get_y();
	}
	res += get_vertex(get_dim() - 1).get_x() * get_vertex(0).get_y();
	res -= get_vertex(0).get_x() * get_vertex(get_dim() - 1).get_y();
	res = abs(res)/2;
	_area = res;
}

void Polygon::print_coords() {
	int size = get_dim();
	for (int i = 0; i < size - 1; i++)
		cout << get_vertex(i) << ", ";
	cout << get_vertex(size - 1) << endl;
}

void Polygon::print_all_info(){
	cout << "Coords of all vertexes: ";
	print_coords();
	cout << "Area: " << get_area << endl;
	cout << "Perimeter: " << get_perimeter << endl;
}