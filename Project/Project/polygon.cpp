#include "polygon.h"
#include "Line.h"
#include "Point.h"
#include "glut.h"

namespace polygon {
	Polygon::Polygon(const vector<Point>& vertexes)
	{
		set_vertexes(vertexes);
		init_area();
		init_perimeter();
	}

	Point Polygon::get_vertex(int i)const {
		if (i >= 0 && i < _vertexes.size())
			return _vertexes[i];
		else
			throw "Index out of bounds";
	}

	void Polygon::set_vertexes(vector<Point> vertexes) {
		if (vertexes.size() < 3)
			throw "Not enough vertexes";
		/*перед добавлением новой вершины проверяем, не является ли
		многогранник самопересекающимся*/
		_vertexes.clear();
		for (size_t i = 0; i < vertexes.size(); i++) {
			for (size_t j = 1; j < i; j++) {
				Segment a = { vertexes[j - 1], vertexes[j] };
				Segment b = { vertexes[i - 1], vertexes[i] };
				if (intersection(a, b))
					throw "Intersection found";
			}
			if (i == vertexes.size() - 1) {
				for (size_t j = 1; j < i; j++) {
					Segment a = { vertexes[j - 1], vertexes[j] };
					Segment b = { vertexes[0], vertexes[i] };
					if (intersection(a, b))
						throw "Intersection found";
				}
			}
		}
		for (size_t i = 0; i < vertexes.size(); i++) {
			Line a = { vertexes[i], vertexes[(i+1) % vertexes.size()] };
			Line b = { vertexes[(i + 1) % vertexes.size()], vertexes[(i + 2) % vertexes.size()] };
			if (if_parallel(a, b)) throw "Invalid polygon";
		}
		for (size_t i = 0; i < vertexes.size(); i++)
			_vertexes.push_back(vertexes[i]);
	}

	void Polygon::init_perimeter() {
		int dim = get_dim();
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

	Polygon& Polygon::operator= (const Polygon& poly) {
		vector<Point> v;
		for (int i = 0; i < poly.get_dim(); i++)
			v.push_back(poly.get_vertex(i));
		this->set_vertexes(v);
		return *this;
	}

	Polygon Polygon::operator+ (const Vector& v) {
		vector<Point> vertexes;
		for (int i = 0; i < get_dim(); i++)
			vertexes.push_back(_vertexes[i] + v);
		return Polygon(vertexes);
	}

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

	double rotation(const Point& p1,const Point& p2,const Point& p3) {
		Point r1 = p2 - p1;
		Point r2 = p3 - p2;
		double cross = r1.get_x() * r2.get_y() - r1.get_y() * r2.get_x();
		if (cross < 0) return -1;
		if (cross > 0) return 1;
		return 0;
	}
	
	Ray Polygon::bisector(Point vertex)const {
		size_t num = -1;
		for (int i = 0; i < get_dim(); i++)
			if (_vertexes[i] == vertex) num = i;
		if (num == -1)
			throw invalid_argument("Point is not a vertex");
		//строим два вектора выходящих из вершины и нормируем их
		Vector v1(_vertexes[num], _vertexes[(num + 1) % get_dim()]);
		Vector v2(_vertexes[num], _vertexes[(num - 1) % get_dim()]);
		v1.normalize(); 
		v2.normalize();
		//вектор биссектрисы есть сумма этих норм. векторов
		Vector v3 = v1 + v2;
		Ray res(vertex, v3);
		return res;
	}

	bool cop(const Point& p1, const Point& p2) {
		//Если точка р1 лежит на оси OY и х>0, то p2>p1
		if (p1.get_y() == 0 && p1.get_x() > 0)
			return true; 

		//Если точка р2 лежит на оси ОY и х>0, то p1>p2
		if (p2.get_y() == 0 && p2.get_x() > 0)
			return false; 

		/*Лежит ли точка р1 в градусной мере от (0,180) -1 и 2 четверть
		и лежит ли точка р2 в градусной мере от (180,360) - 3 и 4 четверть*/
		if (p1.get_y() > 0 && p2.get_y() < 0)
			return true; 

		/*Лежит ли точка р1 в градусной мере от (180,360) -3 и 4 четверть
		и лежит ли точка р2 в градусной мере от (0,180) - 1 и 2 четверть*/
		if (p1.get_y() < 0 && p2.get_y() > 0)
			return false;

		//Расположение точки р1 по часовой стрелки отн-но точки р2
		return (p1.get_x() * p2.get_y() - p1.get_y() * p2.get_x()) > 0; 
	}

	Polygon convex_shell(vector<Point> points) {
		sort(points.begin(), points.end(), cop);
		int n = points.size();
		vector <Point> top = { points[0] };
		vector <Point> bottom = { points[0] };

		for (int i = 1; i < n; i++) {
			if (rotation(points[0], points[n - 1], points[i]) >= 0) {
				while (top.size() > 1 && rotation(top[top.size() - 2], top[top.size() - 1], points[i]) >= 0)
					top.pop_back();
				top.push_back(points[i]);
			}
			else {
				while (bottom.size() > 1 && rotation(bottom[bottom.size() - 2], bottom[bottom.size() - 1], points[i]) <= 0)
					bottom.pop_back();
				bottom.push_back(points[i]);
			}
		}

		while (bottom.size() > 1 && rotation(bottom[bottom.size() - 2], bottom[bottom.size() - 1], points[n - 1]) <= 0)
			bottom.pop_back();

		reverse(bottom.begin(), bottom.end());
		for (Point u : bottom)
			top.push_back(u);
		top.pop_back();

		int r = top.size();
		Polygon p = top;
		return p;
	}

	void Polygon::draw()const {
		glColor3d(_image._color.R, _image._color.G, _image._color.B);
		glLineWidth(_image._width);
		if (_image._is_filled)
			glBegin(GL_POLYGON);
		else 
			glBegin(GL_LINE_LOOP);
		for (int i = 0; i < this->get_dim(); i++)
			glVertex2d(get_vertex(i).get_x(), get_vertex(i).get_y());
		glEnd();
	}
}