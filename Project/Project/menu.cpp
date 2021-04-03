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

using namespace std;

const int N = 8; // Количество элементов в меню

int print_menu(string* a) {
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

int main() {
	setlocale(LC_ALL, "");
	string* A = new string[N];
	A[0] = "Действия с прямыми";
	A[1] = "Действия с лучом";
	A[2] = "Действия с треугольником";
	A[3] = "Действия с окружностью";
	A[4] = "Действия с кругом";
	A[5] = "Действия с многоугольником";
	A[6] = "Действия с четырехугольником";
	A[7] = "Действия с векторами";
	while (true) {
		int key = print_menu(A);
		switch (key) {
		case 1: {
			Line::print_line_information();
			break;
		}
		case 2: {
			Ray::print_ray_information();
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
			t1.print_all_info(cout);
			break;
		}
		case 4: {
			double x1, y1, rad;
			cout << "Enter the center and radius of the circle" << endl;
			cin >> x1 >> y1 >> rad;
			Point p(x1, y1);
			Circle c(p, rad);
			cout << "Circle equation" << endl;
			c.print_eq();
			cout << endl << "Length of the circle ";
			cout << c.length() << endl;
			cout << "Enter coordinates of point" << endl;
			cin >> x1 >> y1;
			Point p1(x1, y1);
			double dist = distance(c, p1);
			if (dist != 0) cout << "Distance from this point to the circle" << endl << dist << endl;
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
			polygon::Polygon p;
			cout << "Enter num of vertexes" << endl;
			cout << "Then enter coords of each vertexes in the right order" << endl;
			cin >> p;
			p.print_all_info(cout);
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