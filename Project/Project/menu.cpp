#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <algorithm>

using namespace std;

/*�������� �������*/
void set_color(int sctext, int scfon) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, (scfon << 4) + sctext);
}

/*������ ��������� ����*/
int print_menu_key() {
	set_color(15, 5);
	cout << "1.�������� � ������" << endl;
	cout << "2.�������� � �����������" << endl;
	cout << "3.�������� � �������������" << endl;
	cout << "4.�������� � ���������������" << endl;
	cout << "5.�����" << endl;
	set_color(15, 10);
	cout << "����� � ����:" << endl;
	int item;
	cin >> item;
	return item;
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	set_color(15, 15);
	int item;
	do {
		item = print_menu_key();
		switch (item)
		{
		case 1:; break;
		case 2:; break;
		case 3:; break;
		case 4:; break;
		case 5: return 0; break;
		default:
			break;
		}
	} while (item != 5);
	return 0;
}