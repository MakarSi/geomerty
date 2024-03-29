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
#include "vector.h"
#include "Ray.h"
#include "quadrangle.h"
#include "menu.h"

using namespace std;

string who_iam(Object* obj) {
	if (dynamic_cast<Point*>(obj) != NULL) return "Point";
	if (dynamic_cast<Circle*>(obj) != NULL) return "Circle";
	if (dynamic_cast<Line*>(obj) != NULL) return "Line";
	if (dynamic_cast<Ray*>(obj) != NULL) return "Ray";
	if (dynamic_cast<Segment*>(obj) != NULL) return "Segment";
	if (dynamic_cast<polygon::Polygon*>(obj) != NULL) {
		if (dynamic_cast<Triangle*>(obj) != NULL)
			return "Triangle";
		if (dynamic_cast<Quadrangle*>(obj) != NULL)
			return "Quadrangle";
		return "Polygon";
	}
	return "I dont kno who you are";
}

int print_menu(string* a, int N) {
	int key = 0, move;
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Select what do you want to work with:\n\n";
		cout << "Press ESC to exit\n";

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
	string* A = new string[8];
	A[0] = "Line";
	A[1] = "Ray";
	A[2] = "Triangle";
	A[3] = "Circle";
	A[4] = "Polygon";
	A[5] = "Output the list of objects";
	A[6] = "Quit the menu to glut";
	while (true) {
		int key = print_menu(A, 7);
		switch (key) {
		case 1: {
			line_menu(ptr);
			break;
		}
		case 2: {
			ray_menu(ptr);
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
			polygon_menu(ptr);
			break;
		}
		case 6: {
			node<Object*>* tmp_ptr = ptr->head();
			int i = 1;
			while (tmp_ptr != nullptr) {
				cout << i << ". " << who_iam(tmp_ptr->key) << endl;
				tmp_ptr->key->print_info();
				tmp_ptr = tmp_ptr->next;
				i++;
			}
			system("pause");
			break;
		}
		case 7: {
			return 0;
		}
		case 8: {
			exit(0);
		}
		default: break;
		}
	}
}

int save_in(istream& in) {
	string n0;
	int n = -1;
	getline(cin, n0);
	if (n0.size() > 9) return -1; //���� ����� ������ ������ 9, �� ���������� -1, ��� ��� ��� ����� �� ������� ��������
	for (int i = 0; i < n0.size(); i++) {
		if (n0[i] > '9' || n0[i] < '0') {
			n = -1;
			break;
		}
		n = stoi(n0);
	}
	return n;
}

int polygon_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[5];
	A[0] = "Add new polygon";
	A[1] = "Print info about polygon";
	A[2] = "Shift polygon by vector";
	A[3] = "Find a bisector";
	A[4] = "Go back";

	while (true) {
		int key = print_menu(A, 5);
		switch (key) {
		case 1: {
			polygon::Polygon* p = input_polygon(cin);
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			if (p != nullptr) {
				ptr->push_back(p);
			}
			else system("pause");
			break;
		}
		case 2: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<polygon::Polygon*>((*ptr)[n - 1]) != NULL)
				dynamic_cast<polygon::Polygon*>((*ptr)[n - 1])->print_info();
			else cout << "This object isn`t a polygon" << endl;
			break;
		}
		case 3: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<polygon::Polygon*>((*ptr)[n - 1]) != NULL) {
				cout << "Input vector" << endl;
				Vector v;
				cin >> v;
				cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
				Object* tmp = (*ptr)[n - 1];
				*dynamic_cast<polygon::Polygon*>((*ptr)[n - 1]) = *dynamic_cast<polygon::Polygon*>((*ptr)[n - 1]) + v;
			}
			else cout << "This object isn`t a polygon" << endl;
			break;
		}
		case 4: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num of object from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			polygon::Polygon* t_ptr = dynamic_cast<polygon::Polygon*>((*ptr)[n - 1]);
			if (t_ptr != NULL) {
				int k = -1;
				while (k < 0 || k > t_ptr->get_dim()-1) {
					cout << "Enter num of vertex from 1 to " << t_ptr->get_dim() << endl;
					k = save_in(cin) - 1;
				}
				Ray* ray = new Ray;
				*ray = t_ptr->bisector(t_ptr->get_vertex(k));
				ptr->push_back(ray);
			}
			else cout << "This object isn`t a polygon" << endl;
			break;
		}
		case 5: {
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

int circle_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[8];
	A[0] = "Add new circle";
	A[1] = "Print info about circle";
	A[2] = "Shift circle by vector";
	A[3] = "Finding tangents for point on circle";
	A[4] = "Finding tangents for point out of circle";
	A[5] = "Finding the intersection points of two circles";
	A[6] = "Belong point to circle";
	A[7] = "Go back";

	while (true) {
		int key = print_menu(A, 8);
		switch (key) {
		case 1: {
			Circle* c = input_circle(cin);
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			if (c != nullptr) {
				ptr->push_back(c);
			}
			else system("pause");
			break;
		}
		case 2: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Circle*>((*ptr)[n - 1]) != NULL)
				dynamic_cast<Circle*>((*ptr)[n - 1])->print_info();
			else cout << "This object isn`t a circle" << endl;
			break;
		}
		case 3: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Circle*>((*ptr)[n - 1]) != NULL) {
				cout << "Input vector" << endl;
				Vector v;
				cin >> v;
				cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
				Object* tmp = (*ptr)[n - 1];
				*dynamic_cast<Circle*>((*ptr)[n - 1]) = *dynamic_cast<Circle*>((*ptr)[n - 1]) + v;
			}
			else cout << "This object isn`t a circle" << endl;
			break;
		}
		case 4: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Circle*>((*ptr)[n - 1]) == NULL) {
				cout << "This object isn`t a circle" << endl;
				system("pause");
				break;
			}
			cout << "Enter the coordinates of the point through which the tangents pass" << endl;
			Point p;
			cin >> p;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			Line* tmp = new Line;
			*tmp = tangent_line(p, *dynamic_cast<Circle*>((*ptr)[n - 1]));
			if (tmp->is_undef()) {
				cout << "Point is inside the circle" << endl;
				break;
			}
			cout << *tmp << endl;
			ptr->push_back(tmp);
			break;
		}
		case 5: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Circle*>((*ptr)[n - 1]) == NULL) {
				cout << "This object isn`t a circle" << endl;
				break;
			}
			cout << "Enter the coordinates of the point through which the tangents pass" << endl;
			Point p;
			cin >> p;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			Line tmp1, tmp2;
			tangent_lines(p, *dynamic_cast<Circle*>((*ptr)[n - 1]), tmp1, tmp2);
			if (tmp1.is_undef()) {
				cout << "Point is on circle or inside it" << endl;
				break;
			}
			cout << tmp1 << endl << tmp2 << endl;
			Line* line1 = new Line;
			*line1 = tmp1;
			ptr->push_back(line1);
			Line* line2 = new Line;
			*line2 = tmp2;
			ptr->push_back(line2);
			break;
		}
		case 6: {
			if (ptr->size() == 0) break;
			int n1 = -1;
			while (n1 < 1 || n1 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n1 = save_in(cin);
			}
			if (dynamic_cast<Circle*>((*ptr)[n1 - 1]) == NULL) {
				cout << "This object isn`t a circle" << endl;
				system("pause");
				break;
			}
			int n2 = -1;
			while (n2 < 1 || n2 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n2 = save_in(cin);
			}
			if (dynamic_cast<Circle*>((*ptr)[n2 - 1]) == NULL) {
				cout << "This object isn`t a circle" << endl;
				system("pause");
				break;
			}
			Point* p1 = new Point;
			Point* p2 = new Point;
			intersection(*dynamic_cast<Circle*>((*ptr)[n1 - 1]), *dynamic_cast<Circle*>((*ptr)[n2 - 1]), *p1, *p2);
			if (p1->is_undef()) {
				cout << "No intersection or this is the same circle" << endl;
				system("pause");
				break;
			}
			if (*p1 == *p2) {
				cout << *p1 << endl;
				p1->_image._width = 10;
				ptr->push_back(p1);
				delete p2;
			}
			else {
				cout << *p1 << endl << *p2 << endl;
				p1->_image._width = 10;
				p2->_image._width = 10;
				ptr->push_back(p1);
				ptr->push_back(p2);
			}
			break;
		}
		case 7: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Circle*>((*ptr)[n - 1]) == NULL) {
				cout << "This object isn`t a circle" << endl;
				break;
			}
			cout << "Enter the point" << endl;
			Point p;
			cin >> p;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			if (dynamic_cast<Circle*>((*ptr)[n - 1])->if_belong(p)) cout << "Point is inside of circle" << endl; 
			else cout << "Point isn't inside of circle" << endl;
		}
		case 8: {
			return 0;
		}
		default: break;
		}
	}
}

Circle* input_circle(istream& in) {
	cout << "Enter the center coordinates and the radius value" << endl;
	Circle* c = new Circle;
	try {
		in >> *c;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		delete c;
		c = nullptr;
	}
	return c;
}

int triangle_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[5];
	A[0] = "Add new triangle";
	A[1] = "Print info about triangle";
	A[2] = "Shift triangle by vector";
	A[3] = "Find a normal";
	A[4] = "Go back";

	while (true) {
		int key = print_menu(A, 5);
		switch (key) {
		case 1: {
			Triangle* t = input_triangle(cin);
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			if (t != nullptr) {
				ptr->push_back(t);
			}
			else system("pause");
			break;
		}
		case 2: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Triangle*>((*ptr)[n - 1]) != NULL)
				dynamic_cast<Triangle*>((*ptr)[n - 1])->print_info();
			else cout << "This object isn`t a triangle" << endl;
			break;
		}
		case 3: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<polygon::Polygon*>((*ptr)[n - 1]) != NULL) {
			cout << "Input vector" << endl;
			Vector v;
			cin >> v;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			Object* tmp = (*ptr)[n - 1];
			*dynamic_cast<Triangle*>((*ptr)[n - 1]) = *dynamic_cast<Triangle*>((*ptr)[n - 1]) + v;
			}
			else cout << "This object isn`t a triangle" << endl;
			break;
		}
		case 4: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num of object from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			Triangle* t_ptr = dynamic_cast<Triangle*>((*ptr)[n - 1]);
			if (t_ptr != NULL) {
				int k = -1;
				while (k > 3 || k < 1) {
					cout << "Enter num of vertex from 1 to 3" << endl;
					k = save_in(cin);
				}
				Segment* s = new Segment;
				*s = t_ptr->normal(t_ptr->get_vertex(k - 1));
				cout << *s << endl;
				ptr->push_back(s);
				break;
			}
			else cout << "This object isn`t a triangle" << endl;
			break;
		}
		case 5: {
			return 0;
		}
		default: break;
		}
	}
}

Triangle* input_triangle(istream& in) {
	cout << "Enter the coordinates of the vertices of the triangle: " << endl;
	Triangle* t = new Triangle;
	try {
		in >> *t;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		delete t;
		t = nullptr;
	}
	return t;
}

int line_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[9];
	A[0] = "Add new line";
	A[1] = "Print line equation ";
	A[2] = "Shift line by vector";
	A[3] = "Find the angle between straight lines";
	A[4] = "Find the point of intersection of lines";
	A[5] = "Determine in which half-plane point lays";
	A[6] = "Find a perpendicular line through point";
	A[7] = "Find a parallel line through point";
	A[8] = "Go back";

	while (true) {
		int key = print_menu(A, 9);
		switch (key) {
		case 1: {
			Line* l = input_line(cin);
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			if (l != nullptr) {
				ptr->push_back(l);
			}
			else system("pause");
			break;
		}
		case 2: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n - 1]) != NULL)
				dynamic_cast<Line*>((*ptr)[n - 1])->print_info();
			else cout << "This object isn`t a line" << endl;
			break;
		}
		case 3: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n - 1]) != NULL) {
				cout << "Input vector" << endl;
				Vector v;
				cin >> v;
				cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
				Object* tmp = (*ptr)[n - 1];
				*dynamic_cast<Line*>((*ptr)[n - 1]) = *dynamic_cast<Line*>((*ptr)[n - 1]) + v;
			}
			else cout << "This object isn`t a line" << endl;
			break;
		}
		case 4: {
			if (ptr->size() == 0) break;
			int n1 = -1;
			while (n1 < 1 || n1 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n1 = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n1 - 1]) == NULL) {
				cout << "This object isn`t a line" << endl;
				system("pause");
				break;
			}
			int n2 = -1;
			while (n2 < 1 || n2 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n2 = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n2 - 1]) == NULL) {
				cout << "This object isn`t a line" << endl;
				system("pause");
				break;
			}
			cout << "Angle between lines = " << angle_between_lines(*dynamic_cast<Line*>((*ptr)[n1 - 1]), *dynamic_cast<Line*>((*ptr)[n2 - 1])) << endl;
			break;

		}
		case 5: {
			if (ptr->size() == 0) break;
			int n1 = -1;
			while (n1 < 1 || n1 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n1 = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n1 - 1]) == NULL) {
				cout << "This object isn`t a line" << endl;
				system("pause");
				break;
			}
			int n2 = -1;
			while (n2 < 1 || n2 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n2 = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n2 - 1]) == NULL) {
				cout << "This object isn`t a line" << endl;
				system("pause");
				break;
			}
			if (if_parallel(*dynamic_cast<Line*>((*ptr)[n1 - 1]), *dynamic_cast<Line*>((*ptr)[n2 - 1]))) cout << "This lines are parallel" << endl;
			else {
				Point* p = new Point;
				*p = intersection_point(*dynamic_cast<Line*>((*ptr)[n1 - 1]), *dynamic_cast<Line*>((*ptr)[n2 - 1]));
				p->_image._width = 10;
				ptr->push_back(p);
				cout << "Point of intersection of lines " << *p << endl;
			}
			break;
		}
		case 6: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n - 1]) == NULL) {
				cout << "This object isn`t a line" << endl;
				system("pause");
				break;
			}
			Point p;
			cout << "Input point" << endl;
			cin >> p;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			if (point_in_halfplane(p, *dynamic_cast<Line*>((*ptr)[n - 1])) == -1) cout << "This point lies in the negative half_plane" << endl;
			else if (point_in_halfplane(p, *dynamic_cast<Line*>((*ptr)[n - 1])) == 0) cout << "This point lies on a line" << endl;
			else cout << "This point lies in the positive half_plane" << endl;
			break;
		}
		case 7: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n - 1]) == NULL) {
				cout << "This object isn`t a line" << endl;
				system("pause");
				break;
			}
			Point p;
			cout << "Input point" << endl;
			cin >> p;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			Line* l = new Line;
			*l = dynamic_cast<Line*>((*ptr)[n - 1])->normal_line(p);
			cout << *l << endl;
			ptr->push_back(l);
			break;
		}
		case 8: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Line*>((*ptr)[n - 1]) == NULL) {
				cout << "This object isn`t a line" << endl;
				system("pause");
				break;
			}
			Point p;
			cout << "Input point" << endl;
			cin >> p;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			Line* l = new Line;
			if (dynamic_cast<Line*>((*ptr)[n - 1])->if_belong(p)) {
				cout << "This point belong to the line" << endl;
				break;
			}
			*l = parallel_line_through_point(*dynamic_cast<Line*>((*ptr)[n - 1]), p);
			cout << *l << endl;
			ptr->push_back(l);
			break;
		}
		case 9: {
			return 0;
		}
		default: break;
		}
	}
}

Line* input_line(istream& in) {
	cout << "Enter the coefficients of the equation of line: Ax+By+C=0" << endl;
	Line* l = new Line;
	try {
		in >> *l;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		delete l;
		l = nullptr;
	}
	return l;
}

int ray_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[7];
	A[0] = "Add new ray";
	A[1] = "Print info about ray";
	A[2] = "Shift ray by vector";
	A[3] = "Angle between rays";
	A[4] = "Instersection point of two rays";
	A[5] = "Belong point to ray";
	A[6] = "Go back";

	while (true) {
		int key = print_menu(A, 7);
		switch (key) {
		case 1: {
			Ray* r = input_ray(cin);
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
			if (r != nullptr) {
				ptr->push_back(r);
			}
			else system("pause");
			break;
		}
		case 2: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Ray*>((*ptr)[n - 1]) != NULL)
				dynamic_cast<Ray*>((*ptr)[n - 1])->print_info();
			else cout << "This object isn`t a ray" << endl;
			break;
		}
		case 3: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Ray*>((*ptr)[n - 1]) != NULL) {
				cout << "Input vector" << endl;
				Vector v;
				cin >> v;
				cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� \n
				Object* tmp = (*ptr)[n - 1];
				*dynamic_cast<Ray*>((*ptr)[n - 1]) = *dynamic_cast<Ray*>((*ptr)[n - 1]) + v;
			}
			else cout << "This object isn`t a ray" << endl;
			break;
		}
		case 4: {
			if (ptr->size() == 0) break;
			int n1 = -1;
			while (n1 < 1 || n1 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n1 = save_in(cin);
			}
			if (dynamic_cast<Ray*>((*ptr)[n1 - 1]) == NULL) {
				cout << "This object isn`t a ray" << endl;
				system("pause");
				break;
			}
			int n2 = -1;
			while (n2 < 1 || n2 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n2 = save_in(cin);
			}
			if (dynamic_cast<Ray*>((*ptr)[n2 - 1]) == NULL) {
				cout << "This object isn`t a ray" << endl;
				system("pause");
				break;
			}
			cout << "The angle between rays is " << angle_between_rays(*dynamic_cast<Ray*>((*ptr)[n1 - 1]), *dynamic_cast<Ray*>((*ptr)[n2 - 1])) << endl;
			break;
		}
		case 5: {
			if (ptr->size() == 0) break;
			int n1 = -1;
			while (n1 < 1 || n1 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n1 = save_in(cin);
			}
			if (dynamic_cast<Ray*>((*ptr)[n1 - 1]) == NULL) {
				cout << "This object isn`t a ray" << endl;
				system("pause");
				break;
			}
			int n2 = -1;
			while (n2 < 1 || n2 > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n2 = save_in(cin);
			}
			if (dynamic_cast<Ray*>((*ptr)[n2 - 1]) == NULL) {
				cout << "This object isn`t a ray" << endl;
				system("pause");
				break;
			}
			if (intersection_point_existence(*dynamic_cast<Ray*>((*ptr)[n1 - 1]), *dynamic_cast<Ray*>((*ptr)[n2 - 1])))
				cout << "These two rays have the intersection point: " << ray_intersection_point(*dynamic_cast<Ray*>((*ptr)[n1 - 1]), *dynamic_cast<Ray*>((*ptr)[n2 - 1])) << endl;
			else cout << "These two rays have no intersection point" << endl;
			break;
		}
		case 6: {
			if (ptr->size() == 0) break;
			int n = -1;
			while (n < 1 || n > ptr->size()) {
				cout << "Enter num from 1 to " << ptr->size() << endl;
				n = save_in(cin);
			}
			if (dynamic_cast<Ray*>((*ptr)[n - 1]) == NULL) {
				cout << "This object isn`t a ray" << endl;
				system("pause");
				break;
			}
			cout << "Enter the point" << endl;
			Point p;
			cin >> p;
			cin.ignore(32767, '\n'); //���������� �� 32767 �������� �� �������� ������ �� ��������� 
			if (dynamic_cast<Ray*>((*ptr)[n - 1])->if_belong(p))
				cout << "Point lies on the ray" << endl;
			else cout << "Point don't lies on the ray" << endl;
			break;
		}
		case 7: {
			return 0;
		}
		default: break;
		}
	}
}

Ray* input_ray(istream& in) {
	cout << "Input the begging of the ray and the vector "<<endl;
	Ray* r = new Ray;
	try {
		in >> *r;
	}
	catch (const char* exception) {
		cout << "Error: " << exception << endl;
		delete r;
		r = nullptr;
	}
	return r;
}