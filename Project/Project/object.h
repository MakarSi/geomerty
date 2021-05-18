#pragma once
#define eps 0.000001
#include "glut.h"

struct color { 
	double R, G, B; 
	color() { R = 0; G = 0, B = 0; }
	color(double r, double g, double b) { R = r; G = g; B = b; }
};

class Object
{
public:
	color color;
	bool is_field = false;
	virtual void draw()const = 0;
};