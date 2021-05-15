#include <iostream>
#include "glut.h"
#include "menu.h"
#include <deque>
#include "triangle.h"

using namespace std;

GLint Width = 1920, Height = 1080;
deque<Object*> obj_buff;
deque<Object*> undo_obj_buff;
deque<Point*> points_buff;

void Display(void);
void net_drawing();
void Reshape(GLint w, GLint h);
void mouseButton(int button, int state, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);

int main(int argc, char* argv[]) {
	menu(&obj_buff);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("geomerty");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(mouseButton);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
	return 0;
}

void Display(void)
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	net_drawing();
	for (int i = 0; i < obj_buff.size(); i++)
		obj_buff[i]->draw();
	for (int i = 0; i < points_buff.size(); i++)
		points_buff[i]->draw();
	glFinish();
	glutSwapBuffers();
}

void net_drawing()
{
	Line l;
	for (int i = -1000; i <= 1000; i += 50)
	{
		glLineWidth(1);
		l = Line(Point(1000, double(i)), Point(-1000, double(i)));
		l.draw();
		l = Line(Point(double(i), 1000), Point(double(i), -1000));
		l.draw();
	}
	glLineWidth(2);;
	l = Line(Point(1000, 0), Point(-1000, 0));
	l.draw();
	l = Line(Point(0, 1000), Point(0, -1000));
	l.draw();
	glLineWidth(1.5);
}


void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-Width / 2, Width / 2, -Height / 2, Height / 2);
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
	//клавиша а/ф - создать прямую, треугольник, многоугольник
	if (key == 97 || key == 65 || key == 212 || key == 244) {
		switch (points_buff.size()) {
			case 0: break;
			case 1: break;
			case 2: {
				Line* l = new Line(*points_buff[0], *points_buff[1]);
				obj_buff.push_back(l);
				points_buff.clear();
				break;
			}
			case 3: {
				vector<Point> v;
				for (int i = 0; i < points_buff.size(); i++)
					v.push_back(*points_buff[i]);
				Triangle* tr = new Triangle(v);
				obj_buff.push_back(tr);
				points_buff.clear();
				break;
			}
			default: {
				vector<Point> v;
				for (int i = 0; i < points_buff.size(); i++)
					v.push_back(*points_buff[i]);
				try {
					polygon::Polygon* poly = new polygon::Polygon(v);
					obj_buff.push_back(poly);
				}
				catch (const char* exception) {
						cerr << exception;
				}
				points_buff.clear();
				break;
			}
		}
	}
	// клавиша с/с - создать окружность
	if (key == 67 || key == 99 || key == 209 || key == 241) {
		if (points_buff.size() == 2) {
			double d = distance(*points_buff[0], *points_buff[1]);
			Circle* c = new Circle(*points_buff[0], d);
			obj_buff.push_back(c);
			points_buff.clear();
		}
	}
	//удалить объект с экрана alt + z
	if (key == 90 || key == 122 || key == 223 || key == 255) {
		if (glutGetModifiers() == GLUT_ACTIVE_ALT && !obj_buff.empty()) {
			undo_obj_buff.push_back(obj_buff.back());
			obj_buff.pop_back();
		}
	}
	//вернуть объект на экран alt + y
	if (key == 89 || key == 121 || key == 205 || key == 237) {
		if (glutGetModifiers() == GLUT_ACTIVE_ALT && !undo_obj_buff.empty()) {
			obj_buff.push_back(undo_obj_buff.back());
			undo_obj_buff.pop_back();
		}
	}
	//удалить точки с экрана alt + x
	if (key == 88 || key == 120 || key == 215 || key == 247) {
		if (glutGetModifiers() == GLUT_ACTIVE_ALT && !points_buff.empty())
			points_buff.pop_back();
	}
	// m/ь - выход в консольно меню
	if (key == 77 || key == 109 || key == 220 || key == 252)
		menu(&obj_buff);
	//esc - выход
	if (key == 27)
		exit(0);
	glutPostRedisplay();
}