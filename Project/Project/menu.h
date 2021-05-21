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
void print_info(const polygon::Polygon&, ostream&);
void print_coords(const polygon::Polygon&, ostream&);
polygon::Polygon* input_polygon(istream&);

/*���� ������ ��� ����������*/
int circle_menu(deque<Object*>*);
/*���������� ����� ����������
���� ������� ��������� �������� <=0, �� ������������� ��� ������������� �������� 1*/
Circle* input_circle(istream&);
/*������ ���������� �� ���������� (��������� ���������� � �� �����)*/
void print_info(Circle c, ostream& out);

/*���� ������ ��� ������������*/
int triangle_menu(deque<Object*>*);
Triangle* input_triangle(istream&);

/*���� ��� ������*/
int line_menu(deque<Object*>* ptr);
/*���������� ������ � ������������ ������*/
Line* input_line(istream&);
/*������ ���������� �� ������� - ��������� ������*/
void print_info(Line l, ostream& out);

/*���� ������ ����*/
int ray_menu(deque<Object*>*);
void print_info(const Ray&, ostream&);
Ray* input_ray(istream&);