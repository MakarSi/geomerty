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

int menu(deque<Object*>* ptr) {
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
			triangle_menu(ptr);
			break;
		}
		case 4: {
			circle_menu(ptr);
			break;
		}
		case 5: {
			//ring_menu();
			break;
		}
		case 6: {
			polygon_menu(ptr);
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

int polygon_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[4];
	A[0] = "Add new polygon";
	A[1] = "Print info about polygon";
	A[2] = "Shift polygon by vector";
	A[3] = "Go back";

	vector<polygon::Polygon*> polygons;
	while (true) {
		int key = print_menu(A, 4);
		switch (key) {
		case 1: {
			polygon::Polygon* p = input_polygon(cin);
			if (p != nullptr) {
				polygons.push_back(p);
			}
			else system("pause");
			break;
		}
		case 2: {
			if (polygons.size() == 0) break;
			int n = -1;
			while (n < 1 || n > polygons.size()) {
				cout << "Enter num from 1 to " << polygons.size() << endl;
				cin >> n;
			}
			print_info(*polygons[n-1], cout);
			break;
		}
		case 3: {
			if (polygons.size() == 0) break;
			int n = -1;
			while (n < 1 || n > polygons.size()) {
				cout << "Enter num from 1 to " << polygons.size() << endl;
				cin >> n;
			}
			cout << "Input vector" << endl;
			Vector v;
			cin >> v;
			*polygons[n-1] = *polygons[n-1] + v;
			break;
		}
		case 4: {
			for (int i = 0; i < polygons.size(); i++)
				(*ptr).push_back(polygons[i]);
			return 0;
		}
		default: break;
		}
	}
}

polygon::Polygon* input_polygon(istream& in) {
	cout << "Enter num of vertexes" << endl;
	cout << "Then enter coords of each vertexes in the right order" << endl;
	polygon::Polygon* p = new polygon::Polygon;
	try {
		in >> *p;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		delete p;
		p = nullptr;
	}
	return p;
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

int circle_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[6];
	A[0] = "Add new circle";
	A[1] = "Print info about circle";
	A[2] = "Shift circle by vector";
	A[3] = "Finding tangents to a circle";
	A[4] = "Finding the intersection points of two circles";
	A[5] = "Go back";

	vector<Circle> circles;

	while (true) {
		int key = print_menu(A, 6);
		switch (key) {
		case 1: {
			Circle* c = new Circle;
			input_circle(*c);
			(*ptr).push_back(c);
			circles.push_back(*c);
			break;
		}
		case 2: {
			int n = -1, r = circles.size();
			if (r > 0) {
				while (n < 0 || n >= r) {
					cout << "Enter number of circle from 0 to " << r - 1 << endl;
					cin >> n;
				}
				print_info(circles[n], cout);
				break;
			}
			else {
				cout << "Not enough circles" << endl;
				break;
			}
		}
		case 3: {
			int n = -1, r = circles.size();
			if (r > 0) {
				while (n < 0 || n >= r) {
					cout << "Enter number of circle from 0 to " << r - 1 << endl;
					cin >> n;
				}
				Vector v;
				cout << "Enter the vector" << endl;
				cin >> v;
				circles[n] = circles[n] + v;
				break;
			}
			else {
				cout << "Not enough circles" << endl;
				break;
			}
		}
		case 4: {
			int n = -1, r = circles.size();
			if (r > 0) {
				while (n < 0 || n >= r) {
					cout << "Enter number of circle from 0 to " << r - 1 << endl;
					cin >> n;
				}
				cout << "Enter the coordinates of the point through which the tangents pass" << endl;
				Point p;
				cin >> p;
				double ras = distance(circles[n], p);
				if (ras < circles[n].get_rad()) cout << "The point is located inside the circle" << endl << "It's impossible to construct tangents" << endl;
				/*Если заданная точка принадлежит окружности, то вызывается ф-ция построения касательной через точку на окружности*/
				else if (ras == circles[n].get_rad()) {
					Line* line = new Line;
					*line = tangent_line(p, circles[n]);
					cout << *line << endl;
					(*ptr).push_back(line);
				}
				else {
					/*Почему - то не изменяются прямые после функции*/
					Line* l1 = new Line; Line* l2 = new Line;
					tangent_lines(p, circles[n], *l1, *l2);
					cout << *l1 << endl << *l2 << endl;
					(*ptr).push_back(l1);
					(*ptr).push_back(l2);
				}
				break;
			}
			else {
				cout << "Not enough circles" << endl;
				break;
			}
		}
		case 5: {
			int n1 = -1, r = circles.size();
			/*Проверка хватает ли количества окружностей для нахождения данной задачи*/
			if (r < 2) {
				cout << "Not enough circles" << endl;
				break;
			}
			else {
				while (n1 < 0 || n1 >= r) {
					cout << "Enter number of circle from 0 to " << r - 1 << endl;
					cin >> n1;
				}
				int n2 = -1;
				while (n2 < 0 || n2 >= r || n2 == n1) {
					cout << "Enter number of circle from 0 to " << r - 1 << endl;
					cin >> n2;
				}
				Point p1, p2;
				intersection(circles[n1], circles[n2], p1, p2);
				cout << p1 << endl << p2 << endl;
			}
			break;
		}
		case 6: {
			return 0;
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

int triangle_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[5];
	A[0] = "Add new triangle";
	A[1] = "Print info about triangle";
	A[2] = "Shift triangle by vector";
	A[3] = "Find a normal";
	A[4] = "Go back";
	vector<Triangle> triangles;

	while (true) {
		int key = print_menu(A, 5);
		switch (key) {
		case 1: {
			Triangle* t = new Triangle;
			input_triangle(*t);
			(*ptr).push_back(t);
			triangles.push_back(*t);
			break;
		}
		case 2: {
			int n = -1;
			while (n < 0 || n >= triangles.size()) {
				cout << "Enter num from 0 to " << triangles.size() - 1;
				cin >> n;
			}
			print_info(triangles[n], cout);
			break;
		}
		case 3: {
			int n = -1;
			while (n < 0 || n >= triangles.size()) {
				cout << "Enter num from 0 to " << triangles.size() - 1;
				cin >> n;
			}
			Vector v;
			cin >> v;
			triangles[n] = triangles[n] + v;
			break;
		}
		case 4: {
			int n = -1, k = -1;
			while (n < 0 || n >= triangles.size()) {
				cout << "Enter num from 0 to " << triangles.size() - 1;
				cin >> n;
			}
			Point p;
			while (k > 3 || k < 1) {
				cout << "Enter num of vertexes from 1 to 3" << endl;
				cin >> k;
			}
			Segment* s = new Segment;
			*s = triangles[n].normal(triangles[n].get_vertex(k - 1));
			cout << *s << endl;
			(*ptr).push_back(s);
		}
		case 5: {
			return 0;
		}
		default: break;
		}
	}
}

void input_triangle(Triangle& t) {
	cout << "Enter 3"<<endl;
	cout << "Then enter the coordinates of the vertices of the triangle: " << endl;
	try {
		cin >> t;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		t = {};
	}
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