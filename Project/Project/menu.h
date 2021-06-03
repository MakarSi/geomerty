#pragma once
#include <string>
#include "polygon.h"
#include "circle.h"
#include "triangle.h"
#include "deque.h"
using namespace std;

int print_menu(string*, int);
int menu(deque<Object*>*);

//���� ��� ��������������
int polygon_menu(deque<Object*>*);
void print_coords(const polygon::Polygon&, ostream&);
polygon::Polygon* input_polygon(istream&);

/*���� ������ ��� ����������*/
int circle_menu(deque<Object*>*);
/*���� ����������*/
Circle* input_circle(istream&);

/*���� ������ ��� ������������*/
int triangle_menu(deque<Object*>*);
Triangle* input_triangle(istream&);

/*���� ��� ������*/
int line_menu(deque<Object*>* ptr);
/*���� ������*/
Line* input_line(istream&);

/*���� ������ ����*/
int ray_menu(deque<Object*>*);
/*���� ����*/
Ray* input_ray(istream&);

//���������� ����(���� ������� ����� 1 �����, �� ������������ ���, ����� -1)
int save_in(istream& cin);