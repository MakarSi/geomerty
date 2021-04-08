#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <algorithm>
#include <string>
#include "point.h"
#include "circle.h"
#include "triangle.h"
#include "line.h"
#include "polygon.h"
#include "segment.h"
#include "ring.h"
#include "vector.h"
#include "Ray.h"
#include "quadrangle.h"
#include "menu.h"

using namespace std;

int print_menu(string* a, int N) {
	int key = 0, move;
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Выберите пункт меню:\n\n";
		cout << "Введите ESC, чтобы выйти\n";

		for (int i = 0; i < N; i++) {
			if (i != key) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << i + 1 << ". " << a[i] << endl;
			}//else cout << "\x1B[34m" << i + 1 << ". " << a[i] << "\033[0m\n";
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				cout << i + 1 << ". " << a[i] << endl;
			}
		}

		cout << '\n';
		move = _getch();

		if (move == 27) {
			system("cls");
			return N + 1;
		}

		if (move == 224) move = _getch();

		if (move == 13) {
			system("cls");
			return key + 1;
		}
		else if (move == 72) key = ((key - 1) % N + N) % N;
		else if (move == 80) key = (key + 1) % N;

		system("cls");
	}

	return key;
}

int menu() {
	setlocale(LC_ALL, "");
	string* A = new string[8];
	A[0] = "Действия с прямыми";
	A[1] = "Действия с лучом";
	A[2] = "Действия с треугольником";
	A[3] = "Действия с окружностью";
	A[4] = "Действия с кругом";
	A[5] = "Действия с многоугольником";
	A[6] = "Действия с четырехугольником";
	A[7] = "Действия с векторами";
	while (true) {
		int key = print_menu(A, 8);
		switch (key) {
		case 1: {
			Line l;
			l.print_all_info();
			break;
		}
		case 2: {
			Ray r;
			r.print_all_info();
			break;
		}
		case 3: {
			double x1, y1, x2, y2, x3, y3;
			cout << "Enter the coordinates of the vertices of the triangle: ";
			cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			Point p1(x1, y1);
			Point p2(x2, y2);
			Point p3(x3, y3);
			vector<Point>v = { p1,p2,p3 };
			Triangle t1 = Triangle(v);
			if (t1.get_area() == 0) {
				break;
			}
			print_info(t1, cout);
			break;
		}
		case 4: {
			Circle::print_circle_info();
			break;
		}
		case 5: {
			double x1, y1, rad;
			cout << "Enter the center and radius of the ring" << endl;
			cin >> x1 >> y1 >> rad;
			Point p(x1, y1);
			Ring c(p, rad);
			cout << "Area of ring" << endl;
			cout << c.square(c) << endl;
			cout << "Enter an angle to calculate the area of the segment" << endl;
			double angle;
			cin >> angle;
			cout << "Area of serment" << endl;
			cout << c.sector(c, angle) << endl;
		}
		case 6: {
			polygon_menu();
		}
		case 7:
			break;
		case 8: {
			double x1, y1, x2, y2;
			cout << "Enter the coordinates of the vertices of the vector: ";
			cin >> x1 >> y1 >> x2 >> y2;
			Point p1(x1, y1);
			Point p2(x2, y2);
			Vector v1(p1, p2);
			v1.print_all_info();
			break;
		}
		default: break;
		}
	}
}

int polygon_menu() {
	setlocale(LC_ALL, "");
	string* A = new string[3];
	A[0] = "Add new polygon";
	A[1] = "Print info about polygon";
	A[2] = "Shift polygon by vector";

	vector<polygon::Polygon> polygons;

	while (true) {
		int key = print_menu(A, 3);
		switch (key) {
		case 1: {
			polygon::Polygon p;
			input_polygon(p);
			polygons.push_back(p);
			break;
		}
		case 2: {
			int n;
			cin >> n;
			while (n < 0 || n >= polygons.size()) {
				cout << "Enter num from 0 to " << polygons.size() - 1;
				cin >> n;
			}
			print_info(polygons[n], cout);
			break;
		}
		case 3: {
			int n;
			cin >> n;
			while (n < 0 || n >= polygons.size()) {
				cout << "Enter num from 0 to " << polygons.size()-1;
				cin >> n;
			}
			Vector v;
			cin >> v;
			polygons[n] + v;
			break;
		}
		default: break;
		}
	}
}

void input_polygon(polygon::Polygon& p) {
	cout << "Enter num of vertexes" << endl;
	cout << "Then enter coords of each vertexes in the right order" << endl;
	try {
		cin >> p;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		p = {};
	}
}

void print_coords(const polygon::Polygon& p, ostream& out) {
	int size = p.get_dim();
	for (int i = 0; i < size - 1; i++)
		out << p.get_vertex(i) << ", ";
	if (size >= 1 ) out << p.get_vertex(size - 1);
	out << endl;
}

void print_info(const polygon::Polygon& p, ostream& out){
	out << "Coords of all vertexes: ";
	print_coords(p, out);
	out << "Area: " << p.get_area() << endl;
	out << "Perimeter: " << p.get_perimeter() << endl;
}