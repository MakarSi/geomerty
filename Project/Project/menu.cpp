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
	string* A = new string[9];
	A[0] = "Действия с прямыми";
	A[1] = "Действия с лучом";
	A[2] = "Действия с треугольником";
	A[3] = "Действия с окружностью";
	A[4] = "Действия с кругом";
	A[5] = "Действия с многоугольником";
	A[6] = "Действия с четырехугольником";
	A[7] = "Действия с векторами";
	A[8] = "Выйти из меню в glut";
	while (true) {
		int key = print_menu(A, 9);
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
			circle_menu();
			break;
		}
		case 5: {
			//ring_menu();
			break;
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
		case 9: {
			return 0;
		}
		default: break;
		}
	}
}

int polygon_menu() {
	setlocale(LC_ALL, "");
	string* A = new string[4];
	A[0] = "Add new polygon";
	A[1] = "Print info about polygon";
	A[2] = "Shift polygon by vector";
	A[3] = "Draw polygon";

	vector<polygon::Polygon> polygons;

	while (true) {
		int key = print_menu(A, 4);
		switch (key) {
		case 1: {
			polygon::Polygon p;
			input_polygon(p);
			polygons.push_back(p);
			break;
		}
		case 2: {
			int n = -1;
			cin >> n;
			while (n < 0 || n >= polygons.size()) {
				cout << "Enter num from 0 to " << polygons.size() - 1;
				cin >> n;
			}
			print_info(polygons[n], cout);
			break;
		}
		case 3: {
			int n = -1;
			while (n < 0 || n >= polygons.size()) {
				cout << "Enter num from 0 to " << polygons.size()-1;
				cin >> n;
			}
			Vector v;
			cin >> v;
			polygons[n] + v;
			break;
		}
		case 4: {
			int n = -1;
			while (n < 0 || n >= polygons.size()) {
				cout << "Enter num from 0 to " << polygons.size() - 1;
				cin >> n;
			}
			polygons[n].draw();
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

int circle_menu() {
	setlocale(LC_ALL, "");
	string* A = new string[4];
	A[0] = "Add new circle";
	A[1] = "Print info about circle";
	A[2] = "Shift circle by vector";
	A[3] = "Finding tangents to a circle";

	vector<Circle> circles;

	while (true) {
		int key = print_menu(A, 4);
		switch (key) {
		case 1: {
			Circle c;
			input_circle(c);
			circles.push_back(c);
			break;
		}
		case 2: {
			int n=-1;
			int r = circles.size();
			while (n < 0 || n >= r) {
				cout << "Enter num from 0 to " << r - 1 << endl;
				cin >> n;
			}
			print_info(circles[n], cout);
			break;
		}
		case 3: {
			/*
			*/
			break;
		}
		case 4: {
			int n = -1;
			int r = circles.size();
			while (n < 0 || n >= r) {
				cout << "Enter num from 0 to " << r - 1 << endl;
				cin >> n;
			}
			cout << "Enter the coordinates of the point through which the tangents pass" << endl;
			Point p;
			cin >> p;
			Line line;
			double ras=distance(circles[n],p);
			if (ras < circles[n].get_rad()) cout<<"The point is located inside the circle - it's impossible to construct tangents"<<endl;
			else if (ras == circles[n].get_rad()) {
				line = tangent_line(p,circles[n]);
			} else {
				/*
				*/
			}
			break;
		}
		default: break;
		}
	}
}

void input_circle(Circle& c) {
	cout << "Enter the center coordinates and the radius value" << endl;
	try {
		cin >> c;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		c = {};
	}
}

void print_info(Circle c, ostream& out) {
	out << "The circle equation" << endl;
	c.print_eq();
	out << "Length of the circle = ";
	out<<c.length()<<endl;
}

//int ring_menu() {
//	setlocale(LC_ALL, "");
//	string* A = new string[4];
//	A[0] = "Add new circle";
//	A[1] = "Print info about circle";
//	A[2] = "Shift circle by vector";
//
//	vector<Ring> rings;
//
//	while (true) {
//		int key = print_menu(A, 3);
//		switch (key) {
//		case 1: {
//			Ring r;
//			input_ring(r);
//			rings.push_back(r);
//			break;
//		}
//		case 2: {
//			int n = -1;
//			int r = rings.size();
//			while (n < 0 || n >= r) {
//				cout << "Enter num from 0 to " << r - 1 << endl;
//				cin >> n;
//			}
//			print_info(rings[n]);
//			break;
//		}
//		default: break;
//		}
//	}
//};
//
//void input_ring(Ring& r) {
//	cout << "Enter the center coordinates and the radius value" << endl;
//	try {
//		cin >> r;
//	}
//	catch (const char* exception) {
//		cout << "Error: " << exception << endl;
//		r = {};
//	}
//}
//
//void print_info(Ring r) {
//	cout << "Area of ring =" <<r.square()<<endl;
//	cout << "Enter the degree measure to calculate the circular segment"<<endl;
//	double angle;
//	cin >> angle;
//	cout << "Area of circular segment =" << r.sector(angle) << endl;
//};