#include "polygon.h"
#include "Line.h"

namespace polygon {
	Polygon::Polygon(vector<Point> vertexes)
	{
		set_vertexes(vertexes);
		init_area();
		init_perimeter();
	}

	Point Polygon::get_vertex(int i)const {
		if (i >= 0 && i < _vertexes.size())
			return _vertexes[i];
		else
			throw invalid_argument("Index out of bounds");
	}

	size_t Polygon::get_dim()const {
		return _vertexes.size();
	}

	double Polygon::get_area()const {
		return _area;
	}

	double Polygon::get_perimeter()const {
		return _perimeter;
	}
		
	void Polygon::set_vertexes(vector<Point> vertexes) {
		if (vertexes.size() < 3 && vertexes.size() != 0)
			throw invalid_argument("Not enough vertexes");
		/*перед добавлением новой вершины проверяем, не является ли
		многогранник самопересекающимся*/
		for (size_t i = 0; i < vertexes.size(); i++) {
			for (size_t j = 1; j < i; j++) {
				Segment a = { vertexes[j - 1], vertexes[j] };
				Segment b = { vertexes[i - 1], vertexes[i] };
				if (intersection(a, b))
					throw invalid_argument("Intersection found");
			}
			if (i == vertexes.size() - 1) {
				for (size_t j = 1; j < i; j++) {
					Segment a = { vertexes[j - 1], vertexes[j] };
					Segment b = { vertexes[0], vertexes[i] };
					if (intersection(a, b))
						throw invalid_argument("Intersection found");
				}
			}
			_vertexes.push_back(vertexes[i]);
		}
	}

	void Polygon::init_perimeter() {
		size_t dim = get_dim();
		if (dim == 0) {
			_perimeter = 0;
			return;
		}
		double res = 0;
		for (int i = 0; i < dim; i++)
			res += distance(get_vertex(i % dim), get_vertex((i + 1) % dim));
		_perimeter = res;
	}

	void Polygon::init_area() {
		int dim = get_dim();
		if (dim == 0) {
			_area = 0;
			return;
		}
		//воспользуемся формулой площади Гаусса
		double res = 0;
		for (int i = 0; i < dim; i++) {
			res += get_vertex(i % dim).get_x() * get_vertex((i + 1) % dim).get_y();
			res -= get_vertex((i + 1) % dim).get_x() * get_vertex(i % dim).get_y();
		}
		res = abs(res) / 2;
		_area = res;
	}

	void Polygon::print_coords(ostream& out)const {
		int size = get_dim();
		for (int i = 0; i < size - 1; i++)
			out << get_vertex(i) << ", ";
		out << get_vertex(size - 1) << endl;
	}

	void Polygon::print_all_info(ostream& out)const {
		out << "Coords of all vertexes: ";
		print_coords(out);
		out << "Area: " << get_area() << endl;
		out << "Perimeter: " << get_perimeter() << endl;
	}
	
	/*
	bool Polygon::operator==(const Polygon& p) {
		if (get_dim() != p.get_dim())
			return false;
		int dim = get_dim();
		for (int i = 0; i < dim; i++) {
			bool equal = true;
			for (int j = 0; j < dim; j++) {
				if (get_vertex(j) != p.get_vertex(j + i)) {
					equal = false;
					break;
				}
				
			}
			if (equal) return equal;
		}
		return false;
	}

	bool Polygon::operator!=(const Polygon& p) {
		if (get_dim() != p.get_dim())
			return true;
		int dim = get_dim();
		for (int i = 0; i < dim; i++) {
			bool equal = false;
			for (int j = 0; j < dim; j++) {
				if (get_vertex(j) != p.get_vertex(j + i)) {
					equal = true;
					break;
				}
			}
			if (!equal) return equal;
		}
		return true;
	}
	*/

	istream& operator>>(istream& in, Polygon& p) {
		int n;
		in >> n;
		vector<Point> vertexes;
		double x, y;
		for (int i = 0; i < n; i++) {
			in >> x >> y;
			Point t = { x, y };
			vertexes.push_back(t);
		}
		p = vertexes;
		return in;
	}
}