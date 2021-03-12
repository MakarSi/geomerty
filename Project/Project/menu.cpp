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

using namespace std;

const int N = 8; // Количество элементов в меню

int print_menu(string* a) {
	int key = 0, move;
	while (true) {
		cout << "Выберите пункт меню:\n\n";
		cout << "Введите ESC, чтобы выйти\n";

		for (int i = 0; i < N; i++) {
			if (i != key) cout << i + 1 << ". " << a[i] << endl;
			else cout << "\x1B[34m" << i + 1 << ". " << a[i] << "\033[0m\n";
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
		if (key == 1);
		  else if (key == 2);
		  else if (key == 3) {
			double x1, y1, x2, y2, x3, y3;
			cout << "Enter the coordinates of the vertices of the triangle: ";
			cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			Point p1(x1, y1);
			Point p2(x2, y2);
			Point p3(x3, y3);
			Triangle t1(p1, p2, p3);
			cout << "Given a triangle with vertices with corodnites: ";
			t1.print_coordinate_of_tops();
			double per = t1.perimeter();
			double sq = t1.square();
			cout << "Perimeter: ";
			cout << per << " Square: " << sq << endl;
		}
		      else if (key == 4);
		        else if (key == 5);
				else if (key == 6) {
			polygon::Polygon p;
			cin >> p;
			p.print_all_info();
		}
		            else if (key == 7);
					else if (key == 8) {
			double x1, y1, x2, y2;
			cout << "Enter the coordinates of the vertices of the vector: ";
			cin >> x1 >> y1 >> x2 >> y2;
			Point p1(x1, y1);
			Point p2(x2, y2);
			Vector v1(p1, p2);
			cout << "Given a vector with corodnites: (";
			cout << v1.x_coordinate_of_vector() << ", " << v1.y_coordinate_of_vector() << ')' << endl;
			cout << "Vector length: " << v1.length() << endl;
			cout << "Scalar product with vector " << endl;
			cout << "Enter the coordinates of the vertices of the vector: ";
			double x3, y3, x4, y4;
			cin >> x3 >> y3 >> x4 >> y4;
			Point p3(x3, y3);
			Point p4(x4, y4);
			Vector v2(p3, p4);
			cout << endl << "Scalar product: " << v1.scalar_product(v2) << endl;
			cout << "vector product with the same vector :" << v1.vector_product(v2) << endl;
		}
		                else break;
	}
}