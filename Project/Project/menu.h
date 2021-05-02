#pragma once
#include <string>
#include "polygon.h"
#include "circle.h"

using namespace std;

int print_menu(string*, int);
int polygon_menu();
int menu();

void print_info(const polygon::Polygon&, ostream&);
void print_coords(const polygon::Polygon&, ostream&);
void input_polygon(polygon::Polygon&);

/*���� ������ ��� ����������*/
int circle_menu();
/*���������� ����� ����������
���� ������� ��������� �������� <=0, �� ������������� ��� ������������� �������� 1*/
void input_circle(Circle& c);
/*������ ���������� �� ���������� (��������� ���������� � �� �����)*/
void print_info(Circle c, ostream& out);

///*���� ������ ��� �����*/
//int ring_menu();
///*���������� ������ �����
//���� ������� ��������� �������� <=0, �� ������������� ��� ������������� �������� 1*/
//void input_ring(Ring& r);
///*������ ���������� � ����� (������� ����� � ��������� ��������)*/
//void print_info(Ring r);