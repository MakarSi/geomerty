#pragma once
#include <string>
#include "polygon.h"
#include "circle.h"
#include "triangle.h"
#include "deque.h"
using namespace std;

int print_menu(string*, int);
int menu(deque<Object*>*);

//Меню для многоугольника
int polygon_menu(deque<Object*>*);
void print_coords(const polygon::Polygon&, ostream&);
polygon::Polygon* input_polygon(istream&);

/*Меню выбора для окружности*/
int circle_menu(deque<Object*>*);
/*Ввод окружности*/
Circle* input_circle(istream&);

/*Меню выбора для треугольника*/
int triangle_menu(deque<Object*>*);
Triangle* input_triangle(istream&);

/*Меню для прямых*/
int line_menu(deque<Object*>* ptr);
/*Ввод прямой*/
Line* input_line(istream&);

/*Меню выбора луча*/
int ray_menu(deque<Object*>*);
/*Ввод луча*/
Ray* input_ray(istream&);

//безопасный ввод(если введено ровно 1 число, то возвращается оно, иначе -1)
int save_in(istream& cin);