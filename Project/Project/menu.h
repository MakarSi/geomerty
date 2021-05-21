#pragma once
#include <string>
#include "polygon.h"
#include "circle.h"
#include "triangle.h"
#include "deque.h"
using namespace std;

int print_menu(string*, int);
int menu(deque<Object*>*);

int polygon_menu(deque<Object*>*);
void print_info(const polygon::Polygon&, ostream&);
void print_coords(const polygon::Polygon&, ostream&);
polygon::Polygon* input_polygon(istream&);

/*���� ������ ��� ����������*/
int circle_menu(deque<Object*>*);
/*���������� ����� ����������
���� ������� ��������� �������� <=0, �� ������������� ��� ������������� �������� 1*/
void input_circle(Circle& c);
/*������ ���������� �� ���������� (��������� ���������� � �� �����)*/
void print_info(Circle c, ostream& out);

/*���� ������ ��� ������������*/
int triangle_menu(deque<Object*>*);
void input_triangle(Triangle& t);

///*���� ������ ��� �����*/
//int ring_menu();
///*���������� ������ �����
//���� ������� ��������� �������� <=0, �� ������������� ��� ������������� �������� 1*/
//void input_ring(Ring& r);
///*������ ���������� � ����� (������� ����� � ��������� ��������)*/
//void print_info(Ring r);