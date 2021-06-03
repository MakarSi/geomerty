#pragma once
#include "glut.h"
#define eps 0.000001

struct color { 
	double R, G, B; 
	color() { R = 0; G = 0, B = 0; }
	color(double r, double g, double b) { R = r; G = g; B = b; }
};

struct image {
	color _color;
	int _width;
	bool _is_filled = false;
	image() { _width = 3; _is_filled = false; }
	image(color color, int width, bool is_filled)
	{
		_color = color;
		_width = 3;
		_is_filled = is_filled;
	}
};

class Object
{
public:
	virtual void draw()const = 0;
	virtual void print_info()const = 0;
	image _image;
};