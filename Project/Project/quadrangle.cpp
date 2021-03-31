#include "quadrangle.h"
#include <vector>
#include <iostream>

using namespace std;

Quadrangle::Quadrangle(vector<Point> vertexes)
{
	set_vertexes(vertexes);
	init_area();
	init_perimeter();
}

void Quadrangle::Quadrangle::set_vertexes(vector<Point> vertexes) {
	/*перед добавлением новой вершины проверяем, не является ли
	многогранник самопересекающимся*/
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 1; j < i; j++) {
			Segment a = { vertexes[j - 1], vertexes[j] };
			Segment b = { vertexes[i - 1], vertexes[i] };
			if (intersection(a, b))
				throw invalid_argument("Intersection found");
		}
		if (i == 3) {
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

Quadrangle Quadrangle::operator+ (const Vector & v) {
	vector<Point> vertexes;
	for (int i = 0; i < get_dim(); i++)
		vertexes.push_back(_vertexes[i] + v);
	return Quadrangle(vertexes);
}