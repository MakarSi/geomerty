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

/*Меню выбора для окружности*/
int circle_menu();
/*Добавление новой окружности
Если радиусу присвоено значение <=0, то автоматически ему присваивается значение 1*/
void input_circle(Circle& c);
/*Печать информации об окружности (уравнение окружности и ее длина)*/
void print_info(Circle c, ostream& out);

///*Меню выбора для круга*/
//int ring_menu();
///*Добавление нового круга
//Если радиусу присвоено значение <=0, то автоматически ему присваивается значение 1*/
//void input_ring(Ring& r);
///*Печать информации о круге (площадь круга и кругового сегмента)*/
//void print_info(Ring r);