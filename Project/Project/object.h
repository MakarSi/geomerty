#pragma once
#define eps 0.000001
#include "glut.h"

struct color { 
	double R, G, B; 
	color() { R = 1; G = 1, B = 1; }
};

class Object
{
public:
	color color;
	virtual void draw() = 0;
};