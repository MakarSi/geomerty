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
		if (key == 1){
			Point a, b;
			Line c, d;
			int k;
			bool f = false;
			cout << "Input two points to get a line\n";
			cin >> a >> b;
			c = Line(a, b);
			cout << "The equation of this line: " << c << endl;
			cout << "Input a point\n";
			cin >> a;
			k = point_in_halfplane(a, c);
			if (k == 1) cout << "The point belongs to the positive half-plane\n";
			else if (k == 0) cout << "The point belongs to the line\n";
			else if (k == -1) cout << "The point belongs to the negative half-plane\n";
			cout << "\nInput two more point to get another line\n";
			cin >> a >> b;
			d = Line(a, b);
			cout << "The equation of the second line: " << d << endl;
			if (if_parallel(c, d))
			{
				if (c == d) f = true;
				if (!f) cout << "These two line are parallel\n";
				else cout << "These two lines are equal\n";
			}
			else cout << "Here's the intersection point of this two lines: " << intersection_point(c, d) << endl;
			cout << "The angle between these two line is: " << angle_between_lines(c, d) << endl;

		}
		else if (key == 2)
		{
			Point p1, p2, k1, k2, k3, k4;
			cout << "Input a point to get the start of the first ray\n";
			cin >> p1;
			cout << "Input two points to get the vector for the first ray\n";
			cin >> k1 >> k2;
			cout << "Input a point to get the start of the second ray\n";
			cin >> p2;
			cout << "Input two points to get the vector for the second ray\n";
			cin >> k3 >> k4;
			Vector v1 = Vector(k1, k2);
			Vector v2 = Vector(k3, k4);
			Ray r1 = Ray(p1, v1), r2 = Ray(p2, v2);
			bool f = intersectrion_point_existence(r1, r2);
			if (f)
				cout << "These two rays have the intersection point: " << ray_intersection_point(r1, r2) << endl;
			else cout << "These two rays have no intersection point\n";
			cout << "Angle between these two rays is: " << angle_between_rays(r1, r2) << endl;
		}
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
			cout << c.length(c) << endl;
			cout << "Enter coordinates of point" << endl;
			cin >> x1 >> y1;
			Point p1(x1, y1);
			double dist = c.dist_circle(c, p1);
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
			polygon::Polygon p;
			cout << "Enter num of vertexes" << endl;
			cout << "Then enter coords of each vertexes in the right order" << endl;
			cin >> p;
			p.print_all_info(cout);
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