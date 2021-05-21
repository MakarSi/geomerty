#pragma once
#include "glut.h"
#define eps 0.000001

struct color { 
	double R, G, B; 
	color() { R = 0; G = 0, B = 0; }
	color(double r, double g, double b) { R = r; G = g; B = b; }
};

class Object
{
public:
	color _color;
	int _width = 3;
	bool _is_field = false;
	virtual void draw()const = 0;
};