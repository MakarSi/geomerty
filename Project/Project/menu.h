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
void print_info(const polygon::Polygon&, ostream&);
void print_coords(const polygon::Polygon&, ostream&);
polygon::Polygon* input_polygon(istream&);

/*Меню выбора для окружности*/
int circle_menu(deque<Object*>*);
/*Добавление новой окружности
Если радиусу присвоено значение <=0, то автоматически ему присваивается значение 1*/
Circle* input_circle(istream&);
/*Печать информации об окружности (уравнение окружности и ее длина)*/
void print_info(Circle c, ostream& out);

/*Меню выбора для треугольника*/
int triangle_menu(deque<Object*>*);
Triangle* input_triangle(istream&);

/*Меню для прямых*/
int line_menu(deque<Object*>* ptr);
/*Считывание прямой и отлавливание ошибок*/
Line* input_line(istream&);
/*Печать информации об ошибках - уравнение прямой*/
void print_info(Line l, ostream& out);

/*Меню выбора луча*/
int ray_menu(deque<Object*>*);
void print_info(const Ray&, ostream&);
Ray* input_ray(istream&);