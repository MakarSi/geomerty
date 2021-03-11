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
		    else if (key == 3);
		      else if (key == 4);
		        else if (key == 5);
		          else if (key == 6);
		            else if (key == 7);
		              else if (key == 8);
		                else break;
	}
}