#pragma once
#include <string>
#include "polygon.h"

using namespace std;

int print_menu(string*, int);
int polygon_menu();
int menu();
void print_info(const polygon::Polygon&, ostream&);
void print_coords(const polygon::Polygon&, ostream&);
void input_polygon(polygon::Polygon&);