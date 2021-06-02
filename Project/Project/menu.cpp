#include <iostream>
#include <ios>
#include <limits>
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
	string* A = new string[8];
	A[0] = "Действия с прямыми";
	A[1] = "Действия с лучом";
	A[2] = "Действия с треугольником";
	A[3] = "Действия с окружностью";
	A[4] = "Действия с многоугольником";
	A[5] = "Выведи список объектов";
	A[6] = "Выйти из меню в glut";
	while (true) {
		int key = print_menu(A, 7);
		switch (key) {
		case 1: {
			line_menu(ptr);
			break;
		}
		case 2: {
			ray_menu(ptr);
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
		}
		case 6: {
			node<Object*>* tmp_ptr = ptr->head();
			int i = 1;
			while (tmp_ptr != nullptr) {
				cout << i << ". " << who_iam(tmp_ptr->key) << endl;
				tmp_ptr = tmp_ptr->next;
				i++;
			}
			system("pause");
			break;
		}
		case 7: {
			return 0;
		}
		default: break;
		}
	}
}

int save_in(istream& in) {
	string n0;
	int n = -1;
	getline(cin, n0);
	if (n0.size() > 9) return -1; //если длина строки больше 9, то возвращаем -1, так как это точно не интовое значение
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
			cin.ignore();
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
			if (dynamic_cast<polygon::Polygon*>((*ptr)[n-1]) != NULL)
				print_info(*dynamic_cast<polygon::Polygon*>((*ptr)[n-1]), cout);
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
				cin.ignore();
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

void print_info(const polygon::Polygon& p, ostream& out){
	out << "Coords of all vertexes: ";
	print_coords(p, out);
	out << "Area: " << p.get_area() << endl;
	out << "Perimeter: " << p.get_perimeter() << endl;
}

int circle_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[7];
	A[0] = "Add new circle";
	A[1] = "Print info about circle";
	A[2] = "Shift circle by vector";
	A[3] = "Finding tangents for point on circle";
	A[4] = "Finding tangents for point out of circle";
	A[5] = "Finding the intersection points of two circles";
	A[6] = "Go back";

	vector<Circle*> circles;

	while (true) {
		int key = print_menu(A, 7);
		switch (key) {
		case 1: {
			Circle* c = input_circle(cin);
			if (c != nullptr) {
				circles.push_back(c);
			}
			else system("pause");
			break;
		}
		case 2: {
			if (circles.size() == 0) break;
			int n = -1;
			while (n < 1 || n > circles.size()) {
				cout << "Enter num from 1 to " << circles.size() << endl;
				cin >> n;
			}
			print_info(*circles[n-1], cout);
			break;
		}
		case 3: {
			if (circles.size() == 0) break;
			int n = -1;
			while (n < 1 || n > circles.size()) {
				cout << "Enter num from 1 to " << circles.size() << endl;
				cin >> n;
			}
			cout << "Input vector" << endl;
			Vector v;
			cin >> v;
			*circles[n-1] = *circles[n-1] + v;
			break;
		}
		case 4: {
			if (circles.size() == 0) break;
			int n = -1;
			while (n < 1 || n > circles.size()) {
				cout << "Enter num from 1 to " << circles.size() << endl;
				cin >> n;
			}
			cout << "Enter the coordinates of the point through which the tangents pass" << endl;
			Point p;
			cin >> p;
			Line tmp = tangent_line(p, *circles[n - 1]);
			if (tmp.is_undef()) {
				cout << "Point is inside the circle";
				system("pause");
				break;
			}
			Line* line = new Line;
			*line = tmp;
			cout << *line << endl;
			(*ptr).push_back(line);
			break;
		}
		case 5: {
			if (circles.size() == 0) break;
			int n = -1;
			while (n < 1 || n > circles.size()) {
				cout << "Enter num from 1 to " << circles.size() << endl;
				cin >> n;
			}
			cout << "Enter the coordinates of the point through which the tangents pass" << endl;
			Point p;
			cin >> p;
			Line tmp1, tmp2;
			tangent_lines(p, *circles[n-1], tmp1, tmp2);
			if (tmp1.is_undef()) {
				cout << "Point is on circle or inside it" << endl;
				system("pause");
				break;
			}
			Line* l1 = new Line; Line* l2 = new Line;
			*l1 = tmp1, * l2 = tmp2;
			cout << *l1 << endl << *l2 << endl;
			(*ptr).push_back(l1);
			(*ptr).push_back(l2);
			break;
		}
		case 6: {
			if (circles.size() < 2) break;
			int n1 = -1, n2 = -1;
			while (n1 < 1 || n1 > circles.size()) {
				cout << "Enter num from 1 to " << circles.size() << endl;
				cin >> n1;
			}
			while (n2 < 1 || n2 > circles.size()) {
				cout << "Enter num from 1 to " << circles.size() << endl;
				cin >> n2;
			}
			Point *p1 = new Point, *p2 = new Point;
			intersection(*circles[n1-1], *circles[n2-1], *p1, *p2);
			if (p1->is_undef()) {
				cout << "No intersection or this is the same circle" << endl;
				system("pause");
				break;
			}
			if (*p1 == *p2) {
				cout << *p1 << endl;
				p1->_image._width = 10;
				(*ptr).push_back(p1);
				delete p2;
			}
			else {
				cout << *p1 << endl << *p2 << endl;
				p1->_image._width = 10;
				p2->_image._width = 10;
				(*ptr).push_back(p1);
				(*ptr).push_back(p2);
			}
			break;
		}
		case 7: {
			for (int i = 0; i < circles.size(); i++)
				(*ptr).push_back(circles[i]);
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

	while (true) {
		int key = print_menu(A, 5);
		switch (key) {
		case 1: {
			Triangle* t = input_triangle(cin);
			cin.ignore();
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
				print_info(*dynamic_cast<Triangle*>((*ptr)[n - 1]), cout);
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
			cin.ignore();
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
	string* A = new string[8];
	A[0] = "Add new line";
	A[1] = "Print line equation ";
	A[2] = "Shift line by vector";
	A[3] = "Find the angle between straight lines";
	A[4] = "Find the point of intersection of lines";
	A[5] = "Determine in which half-plane point lays";
	A[6] = "Find a perpendicular line through point";
	A[7] = "Go back";

	vector<Line*> lines;

	while (true) {
		int key = print_menu(A, 8);
		switch (key) {
		case 1: {
			Line* l = input_line(cin);
			if (l != nullptr) {
				lines.push_back(l);
			}
			else system("pause");
			break;
		}
		case 2: {
			int r = lines.size();
			if (r == 0) break;
			int n = -1;
			while (n < 1 || n > r) {
				cout << "Enter number of lines from 1 to " << r << endl;
				cin >> n;
			}
			print_info(*lines[n - 1], cout);
			break;
		}
		case 3: {
			int r = lines.size();
			if (r == 0) break;
			int n = -1;
			while (n < 1 || n > r) {
				cout << "Enter number of lines from 1 to " << r << endl;
				cin >> n;
			}
			Vector v;
			cout << "Enter the vector" << endl;
			cin >> v;
			*lines[n - 1] = *lines[n - 1] + v;
			break;
		}
		case 4: {
			int r = lines.size();
			int n1 = -1;
			if (r < 2) break;
			while (n1 < 0 || n1 > r) {
				cout << "Enter number of line from 1 to " << r << endl;
				cin >> n1;
			}
			int n2 = -1;
			while (n2 < 0 || n2 > r || n2 == n1) {
				cout << "Enter number of line from 1 to " << r << endl;
				cin >> n2;
			}
			cout << "Angle between lines = " << angle_between_lines(*lines[n1 - 1], *lines[n2 - 1]) << endl;
			break;
		}
		case 5: {
			int r = lines.size();
			if (r < 2) break;
			int n1 = -1;
			while (n1 < 0 || n1 > r) {
				cout << "Enter number of line from 1 to " << r << endl;
				cin >> n1;
			}
			int n2 = -1;
			while (n2 < 0 || n2 > r || n2 == n1) {
				cout << "Enter number of line from 1 to " << r << endl;
				cin >> n2;
			}
			if (if_parallel(*lines[n1 - 1], *lines[n2 - 1])) cout << "This lines are parallel" << endl;
			else {
				Point* p = new Point;
				*p = intersection_point(*lines[n1 - 1], *lines[n2 - 1]);
				p->_image._width = 10;
				ptr->push_back(p);
				cout << "Point of intersection of lines " << endl << *lines[n1 - 1] << " and " << *lines[n2 - 1] << " = " << *p << endl;
			}
			break;
		}
		case 6: {
			int r = lines.size();
			int n = -1;
			if (r == 0) break;
			while (n < 0 || n > r) {
				cout << "Enter number of lines from 1 to " << r << endl;
				cin >> n;
			}
			Point p;
			cout << "Input point" << endl;
			cin >> p;
			if (point_in_halfplane(p, *lines[n - 1]) == -1) cout << "This point lies in the negative half_plane" << endl;
			else if (point_in_halfplane(p, *lines[n - 1]) == 0) cout << "This point lies on a line" << endl;
			else cout << "This point lies in the positive half_plane" << endl;
			break;
		}
		case 7: {
			int r = lines.size();
			if (r == 0) break;
			int n = -1;
			while (n < 0 || n > r) {
				cout << "Enter number of lines from 1 to " << r << endl;
				cin >> n;
			}
			Point p;
			cout << "Input the coordinates of the point" << endl;
			cin >> p;
			Line* l = new Line;
			*l = lines[n - 1]->normal_line(p);
			cout << *l << endl;
			ptr->push_back(l);
			break;
		}
		case 8: {
			for (int i = 0; i < lines.size(); i++)
				(*ptr).push_back(lines[i]);
			return 0;
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

void print_info(Line l, ostream& out) {
	out << "The line equation" << endl;
	l.print_equation();
	cout << endl;
}

int ray_menu(deque<Object*>* ptr) {
	setlocale(LC_ALL, "");
	string* A = new string[6];
	A[0] = "Add new ray";
	A[1] = "Print info about ray";
	A[2] = "Shift ray by vector";
	A[3] = "Angle between rays";
	A[4] = "Instersection point of two rays";
	A[5] = "Go back";

	vector<Ray*> rays;
	while (true) {
		int key = print_menu(A, 6);
		switch (key)
		{
		case 1:
		{
			Ray* r = input_ray(cin);//			cin >> *r;
			if (r != nullptr)
				rays.push_back(r);
			else system("pause");
			break;
		}
		case 2:
		{
			if (rays.size() == 0) break;
			int n = -1;
			while (n < 1 || n > rays.size())
			{
				cout << "Enter num from 1 to " << rays.size() << endl;
				cin >> n;
			}
			print_info(*rays[n - 1], cout);
			break;
		}
		case 3:
		{
			if (rays.size() == 0) break;
			int n = -1;
			while (n < 1 || n > rays.size()) {
				cout << "Enter num from 1 to " << rays.size() << endl;
				cin >> n;
			}
			cout << "Input vector" << endl;
			Vector v;
			cin >> v;
			*rays[n - 1] = *rays[n - 1] + v;
			break;
		}
		case 4:
		{
			int n1 = 0, n2 = 0;
			if (rays.size() < 2) break;
			while (n1 < 1 || n1 > rays.size())
			{
				cout << "Enter the number of the ray from 1  to " << rays.size() << endl;
				cin >> n1;
			}
			while (n2 < 1 || n2 > rays.size() || n1 == n2)
			{
				cout << "Enter the number of the ray from 1 to " << rays.size() << endl;
				cin >> n2;
			}
			cout << "The angle between rays is " << angle_between_rays(*rays[n1 - 1], *rays[n2 - 1]) << endl;
			break;
		}
		case 5:
		{
			int n1 = 0, n2 = 0;
			if (rays.size() < 2) break;
			while (n1 < 1 || n1 > rays.size())
			{
				cout << "Enter the number of the ray from 1  to " << rays.size() << endl;
				cin >> n1;
			}
			while (n2 < 1 || n2 > rays.size() || n1 == n2)
			{
				cout << "Enter the number of the ray from 1 to " << rays.size() << endl;
				cin >> n2;
			}
			if (intersection_point_existence(*rays[n1 - 1], *rays[n2 - 1]))
				cout << "These two rays have the intersection point: " << ray_intersection_point(*rays[n1 - 1], *rays[n2 - 1]) << endl;
			else cout << "These two rays have no intersection point\n";
			break;
		}
		case 6: {
			for (int i = 0; i < rays.size(); i++)
				(*ptr).push_back(rays[i]);
			return 0;
		}
		default: break;
		}
	}
}

Ray* input_ray(istream& in) {
	cout << "Input the begging of the ray and the vector ";
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

void print_info(const Ray& r, ostream& out) {
	out << "The begging of the ray: " << r.get_point() << endl;;
	out << "The vector of the ray " << r.get_vector() << endl;
}