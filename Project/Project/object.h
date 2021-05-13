#pragma once
#define eps 0.000001
#include "glut.h"

struct color { 
	double R, G, B; 
	color() { R = 0; G = 0, B = 0; }
};

class Object
{
public:
	color color;
	bool is_field = false;
	virtual void draw() = 0;
};