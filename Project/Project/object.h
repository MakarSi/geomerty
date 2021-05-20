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
	color color;
	int width = 3;
	bool is_field = false;
	virtual void draw()const = 0;
};