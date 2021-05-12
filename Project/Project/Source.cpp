#include <iostream>
#include "glut.h"
#include "menu.h"
#include <deque>

deque<Object*> objects;
GLint Width = 1920, Height = 1080;

using namespace std;

void Display(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->draw();
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
	glOrtho(0, w, 0, h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void dummy_test() {
	Point p1(100, 100), p2(300, 400), p3(200, 500), p4(100, 500);
	vector<Point> v = { p1, p2, p3, p4 };
	Point* p = new Point(800, 800);
	polygon::Polygon* poly = new polygon::Polygon(v);
	p1 = { 800, 100 }; p2 = { 1100, 100 };
	Line* l = new Line(p1, p2);	
	p1 = {1200, 200}; p2 = {1400, 500};
	Segment* s = new Segment(p1, p2);
	p3 = { 500, 400 };
	Circle* c = new Circle(p3, 25);
	objects.push_back(poly);
	objects.push_back(p);
	objects.push_back(l);
	objects.push_back(s);
	objects.push_back(c);
}

int main(int argc, char* argv[]) {
	menu();
	dummy_test();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("geomerty");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}