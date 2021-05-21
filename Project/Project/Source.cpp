#include <iostream>
#include <glut.h>
#include "menu.h"
#include "deque.h"
#include "triangle.h"
#define BLACK {0,0,0}
#define RED {255,0,0}
#define YELLOW {255,255,0}
#define GREEN {0,255,0}
#define BLUE {0,0,255}

using namespace std;

GLint Width = 1920, Height = 1080;//������ ����
deque<Object*> obj_buff;
deque<Object*> undo_obj_buff;
deque<Point*> points_buff;
color t_color = BLACK;
int t_width = 3;
bool t_field = true;

void Display(void);
void net_drawing();
void Reshape(GLint w, GLint h);
void mouseButton(int button, int state, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void indicate_drawing();

int main(int argc, char* argv[]) {
	menu(&obj_buff);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//��������� ����� �����������
	glutInitWindowSize(Width, Height);//��������� ������� ����
	glutCreateWindow("geomerty");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);//�����
	glutMouseFunc(mouseButton);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
	return 0;
}

void indicate_drawing() {
	Circle c(Point(-Width / 2 + 45, Height / 2 - 45), 30);
	c.color = t_color;
	c.width = t_width;
	c.is_field = t_field;
	c.draw();
}

void Display(void)
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	net_drawing();
	indicate_drawing();
	node<Object*>* obj_ptr = obj_buff.head();
	node<Point*>* point_ptr = points_buff.head();
	while (obj_ptr != nullptr) {
		obj_ptr->key->draw();
		obj_ptr = obj_ptr->next;
	}
	while (point_ptr != nullptr) {
		point_ptr->key->draw();
		point_ptr = point_ptr->next;
	}
	glFinish();
	glutSwapBuffers();
}

/*�����*/
void net_drawing() {
	Line l;
	for (int i = -1000; i <= 1000; i += 50)
	{
		l = Line(Point(1000, double(i)), Point(-1000, double(i)));
		l.width = 1;
		l.draw();
		l = Line(Point(double(i), 1000), Point(double(i), -1000));
		l.width = 1;
		l.draw();
	}

	l = Line(Point(1000, 0), Point(-1000, 0));
	l.width = 4;
	l.draw();
	l = Line(Point(0, 1000), Point(0, -1000));
	l.width = 4;
	l.draw();
}

void Reshape(GLint w, GLint h) {
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-Width / 2, Width / 2, -Height / 2, Height / 2);//����� ���������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Point* p = new Point(x - Width / 2, Height / 2 - y);
		points_buff.push_back(p);
		glutPostRedisplay();
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	bool obj_created = false;
	/*����� ����� � ������� ��������� - �����*/
	if (key == 49) t_color = BLACK;//1 ������
	if (key == 50) t_color = RED;//2 �������
	if (key == 51) t_color = YELLOW;//3 ������
	if (key == 52) t_color = GREEN;//4 �������
	if (key == 53) t_color = BLUE;//5 �����

	/*������� �����*/
	if (key == 61 && t_width < 10) t_width++;//+
	if (key == 45 && t_width >= 2) t_width--;//-

	/*����������� ������*/
	if (key == 48) t_field = !t_field;

	//������� �/� - ������� ������, �����������, �������������
	if (key == 97 || key == 65 || key == 212 || key == 244) {
		switch (points_buff.size()) {
		case 0: break;
		case 1: break;
		case 2: {
			Segment* l = new Segment(*points_buff[0], *points_buff[1]);
			obj_buff.push_back(l);
			obj_created = true;
			break;
		}
		case 3: {
			vector<Point> v;
			for (int i = 0; i < points_buff.size(); i++)
				v.push_back(*points_buff[i]);
			try {
				Triangle* tr = new Triangle(v);
				obj_buff.push_back(tr);
				obj_created = true;
			}
			catch (const char* exception) {
				cerr << exception;
			}
			break;
		}
		default: {
			vector<Point> v;
			for (int i = 0; i < points_buff.size(); i++)
				v.push_back(*points_buff[i]);
			try {
				polygon::Polygon* poly = new polygon::Polygon(v);
				obj_buff.push_back(poly);
				obj_created = true;
			}
			catch (const char* exception) {
				cerr << exception;
			}
			break;
		}
		}
	}
	// ������� �/� - ������� ����������
	if (key == 67 || key == 99 || key == 209 || key == 241) {
		if (points_buff.size() == 2) {
			double d = distance(*points_buff[0], *points_buff[1]);
			Circle* c = new Circle(*points_buff[0], d);
			obj_buff.push_back(c);
			obj_created = true;
		}
	}
	// ������� l/� - ������� ������
	if (key == 76 || key == 108 || key == 228 || key == 196)
	{
		if (points_buff.size() == 2)
		{
			Line* l = new Line(*points_buff[0], *points_buff[1]);
			obj_buff.push_back(l);
			obj_created = true;
		}
	}
	// ������� r/� - ������� ���
	if (key == 82 || key == 114 || key == 202 || key == 234)
	{
		if (points_buff.size() == 2)
		{
			try
			{
				Vector v(*points_buff[0], *points_buff[1]);
				Ray* r = new Ray(*points_buff[0], v);
				obj_buff.push_back(r);
				obj_created = true;
			}
			catch (const char* exception)
			{
				cerr << exception << endl;
			}
		}
	}

	//������� ������ � ������ alt + z
	if (key == 90 || key == 122 || key == 223 || key == 255) {
		if (glutGetModifiers() == GLUT_ACTIVE_ALT && !obj_buff.empty()) {
			undo_obj_buff.push_back(obj_buff.back());
			obj_buff.pop_back();
		}
	}
	//������� ������ �� ����� alt + y
	if (key == 89 || key == 121 || key == 205 || key == 237) {
		if (glutGetModifiers() == GLUT_ACTIVE_ALT && !undo_obj_buff.empty()) {
			obj_buff.push_back(undo_obj_buff.back());
			undo_obj_buff.pop_back();
		}
	}
	//������� ����� � ������ alt + x
	if (key == 88 || key == 120 || key == 215 || key == 247) {
		if (glutGetModifiers() == GLUT_ACTIVE_ALT && !points_buff.empty())
			points_buff.pop_back();
	}
	//������� ������� ������
	if (key == 127) {
		if (!obj_buff.empty())
			obj_buff.pop_back();
	}
	// m/� - ����� � ��������� ����
	if (key == 77 || key == 109 || key == 220 || key == 252)
		menu(&obj_buff);
	//esc - �����
	if (key == 27)
		exit(0);
	if (obj_created) {
		obj_buff.back()->color = t_color;
		obj_buff.back()->is_field = t_field;
		obj_buff.back()->width = t_width;
		points_buff.clear();
	}
	glutPostRedisplay();
}