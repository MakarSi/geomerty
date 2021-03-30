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

using namespace std;

const int N = 8; // ���������� ��������� � ����

int print_menu(string* a) {
	int key = 0, move;
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "�������� ����� ����:\n\n";
		cout << "������� ESC, ����� �����\n";

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
	A[0] = "�������� � �������";
	A[1] = "�������� � �����";
	A[2] = "�������� � �������������";
	A[3] = "�������� � �����������";
	A[4] = "�������� � ������";
	A[5] = "�������� � ���������������";
	A[6] = "�������� � �����������������";
	A[7] = "�������� � ���������";
	vector<Object> objects;
	while (true) {
		int key = print_menu(A);
		if (key == 1) Line::print_line_information();
		else if (key == 2) Ray::print_ray_information();
		    else if (key == 3) {
			double x1, y1, x2, y2, x3, y3;
			cout << "Enter the coordinates of the vertices of the triangle: ";
			cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			Point p1(x1, y1);
			Point p2(x2, y2);
			Point p3(x3, y3);
			Triangle t1(p1, p2, p3);
			t1.print_all_info();
		}
		      else if (key == 4) {
			double x1, y1, rad;
			cout << "Enter the center and radius of the circle" << endl;
			cin >> x1 >> y1 >> rad;
			Point p(x1, y1);
			Circle c(p, rad);
			cout << "Circle equation" << endl;
			c.print_eq(c);
			cout << endl << "Length of the circle ";
			cout << c.length() << endl;
			cout << "Enter coordinates of point" << endl;
			cin >> x1 >> y1;
			Point p1(x1, y1);
			double dist = distance(c, p1);
			if (dist != 0) cout << "Distance from this point to the circle" << endl << dist << endl;
		}
			    else if (key == 5) {
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
				  else if (key == 6) {
			objects.push_back(polygon::Polygon{});
			cout << "Enter num of vertexes" << endl;
			cout << "Then enter coords of each vertexes in the right order" << endl;
		}
		            else if (key == 7);
					  else if (key == 8) {
			double x1, y1, x2, y2;
			cout << "Enter the coordinates of the vertices of the vector: ";
			cin >> x1 >> y1 >> x2 >> y2;
			Point p1(x1, y1);
			Point p2(x2, y2);
			Vector v1(p1, p2);
			v1.print_all_info();
		}
		                else break;
	}
}