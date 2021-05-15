#include <iostream>
#include "glut.h"
#include "menu.h"
#include <deque>
#include "triangle.h"

using namespace std;

GLint Width = 1920, Height = 1080;
deque<Object*> objects;
deque<Point*> points_buff;
void Display(void)
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->draw();
	for (int i = 0; i < points_buff.size(); i++)
		points_buff[i]->draw();
	glFinish();
	glutSwapBuffers();
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
		Point* p = new Point(x - Width/2, Height/2 - y);
		points_buff.push_back(p);
		glutPostRedisplay();
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	//a or A
	if (key == 97 || key == 65) {
		if (points_buff.size() >= 4) {
			vector<Point> v;
			for (int i = 0; i < points_buff.size(); i++)
				v.push_back(*points_buff[i]);
			polygon::Polygon* poly = new polygon::Polygon(v);
			objects.push_back(poly);
			points_buff.clear();
			glutPostRedisplay();
		}
		if (points_buff.size() == 3) {
			vector<Point> v;
			for (int i = 0; i < points_buff.size(); i++)
				v.push_back(*points_buff[i]);
			Triangle* tr = new Triangle(v);
			objects.push_back(tr);
			points_buff.clear();
			glutPostRedisplay();
		}
		if (points_buff.size() == 2) {
			Line* l = new Line(*points_buff[0], *points_buff[1]);
			objects.push_back(l);
			points_buff.clear();
			glutPostRedisplay();
		}
	}
	if (key == 67 || key == 99) {
		if (points_buff.size() == 2){
			double d = distance(*points_buff[0], *points_buff[1]);
			Circle* c = new Circle(*points_buff[0], d);
			objects.push_back(c);
			points_buff.clear();
			glutPostRedisplay();
		}
	}
	//esc
	if (key == 27)
		exit(0);
}

void dummy_test() {
	Point p1(-100, -100), p2(200, -100), p3(200, 200), p4(-100, 200);
	vector<Point> v = { p1, p2, p3, p4 };
	Point* p = new Point(-400, -400);
	polygon::Polygon* poly = new polygon::Polygon(v);
	p1 = { 1000, 0 }; p2 = { -1000, 0 };
	Line* l1 = new Line(p1, p2);	
	p1 = {0, -600}; p2 = {0, 600};
	Line* l2 = new Line(p1, p2);
	Segment* s = new Segment(p1, p2);
	p3 = { 500, 400 };
	Circle* c = new Circle(p3, 25);
	objects.push_back(poly);
	objects.push_back(p);
	objects.push_back(l1);
	objects.push_back(l2);
	objects.push_back(s);
	objects.push_back(c);
}

int main(int argc, char* argv[]) {
	menu(&objects);
	//dummy_test();

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