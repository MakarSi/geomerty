#pragma once
#include "polygon.h"

class Quadrangle : public polygon::Polygon
{
public:
	Quadrangle(vector<Point> vertexes = {});
	void set_vertexes(vector<Point>);
	Quadrangle operator+ (const Vector& v);
};