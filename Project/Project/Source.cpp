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

GLint Width = 1920, Height = 1080;//размер окна
deque<Object*> obj_buff;
deque<Object*> undo_obj_buff;
deque<Point*> points_buff;
image t_image = {BLACK, 3, true};
GLfloat zoom = 1.0;

void Display(void);
void net_drawing();
void Reshape(GLint w, GLint h);
void mouseButton(int button, int state, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void indicate_drawing();

int main(int argc, char* argv[]) {
	menu(&obj_buff);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);//начальный режим отображения
	glutInitWindowSize(Width, Height);//установка размера окна
	glutCreateWindow("geomerty");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);//сетка

	glutMouseFunc(mouseButton);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
	return 0;
}

void indicate_drawing() {
	Circle c(Point((-Width / 2 + 45) / zoom, (Height / 2 - 45) / zoom), 30 / zoom);
	c._image = t_image;
	c.draw();
}

void Display(void)
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	net_drawing();
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
	indicate_drawing();
	glFinish();
	glutSwapBuffers();
}

/*Сетка*/
void net_drawing() {
	Line l;
	for (int i = 0; i >= -30000; i -= 50/zoom)
	{
		l = Line(Point(1000, double(i)), Point(-1000, double(i)));
		l._image._width = 1;
		l.draw();
		l = Line(Point(double(i), 1000), Point(double(i), -1000));
		l._image._width = 1;
		l.draw();
	}

	for (int i = 0; i <= 30000; i += 50 / zoom)
	{
		l = Line(Point(1000, double(i)), Point(-1000, double(i)));
		l._image._width = 1;
		l.draw();
		l = Line(Point(double(i), 1000), Point(double(i), -1000));
		l._image._width = 1;
		l.draw();
	}


	l = Line(Point(1000, 0), Point(-1000, 0));
	l._image._width = 4;
	l.draw();
	l = Line(Point(0, 1000), Point(0, -1000));
	l._image._width = 4;
	l.draw();
}

void Reshape(GLint w, GLint h) {
	Width = w;
	Height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-Width / 2, Width / 2, -Height / 2, Height / 2);//центр координат
	glMatrixMode(GL_MODELVIEW);
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		Point* p = new Point((x - Width / 2)/zoom, (Height / 2 - y)/zoom);
		points_buff.push_back(p);
		glutPostRedisplay();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Point* p = new Point((x - Width / 2) / zoom, (Height / 2 - y) / zoom);
		points_buff.push_back(p);
		glutPostRedisplay();
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	bool obj_created = false;
	/*Выбор цвета с помощью клавитуры - цифры*/
	if (key == 49) t_image._color = BLACK;//1 черный
	if (key == 50) t_image._color = RED;//2 красный
	if (key == 51) t_image._color = YELLOW;//3 желтый
	if (key == 52) t_image._color = GREEN;//4 зеленый
	if (key == 53) t_image._color = BLUE;//5 синий

	//на 6 увеличить на 7 уменьшить
	if (key == 54 && zoom < 10) { zoom *= 1.1; glScalef(1.1, 1.1, 1.1);}
	if (key == 55 && zoom > 0.05) { zoom *= 0.9; glScalef(0.9, 0.9, 0.9);}

	/*Толщина линий*/
	if (key == 61 && t_image._width < 10) t_image._width++;//+
	if (key == 45 && t_image._width >= 2) t_image._width--;//-

	/*Закрашивать внутри*/
	if (key == 48) t_image._is_filled = !t_image._is_filled;

	//клавиша а/ф - создать прямую, треугольник, многоугольник
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
				cerr << exception << endl ;
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
				cerr << exception << endl;
			}
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
			obj_created = true;
		}
	}

	// клавиша l/д - создать прямую
	if (key == 76 || key == 108 || key == 228 || key == 196)
	{
		if (points_buff.size() == 2)
		{
			Line* l = new Line(*points_buff[0], *points_buff[1]);
			obj_buff.push_back(l);
			obj_created = true;
		}
	}

	// клавиша r/к - создать луч
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

	//клавиша v/м - построить выпуклую оболочку
	if (key == 86 || key == 118 || key == 204 || key == 236) {
		if (points_buff.size() > 2) {
			vector <Point> v;
			for (int i = 0; i < points_buff.size(); i++)
				v.push_back(*points_buff[i]);
			try {
				polygon::Polygon* poly = new polygon::Polygon;
				*poly = polygon::convex_shell(v);
				obj_buff.push_back(poly);
				obj_created = true;
			}
			catch (const char* exception) {
				cerr << exception << endl;
			}
		}
	}

	//стереть объект с экрана alt + z
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

	//Удалить верхний объект
	if (key == 127) {
		if (!obj_buff.empty())
			obj_buff.pop_back();
	}

	// m/ь - выход в консольно меню
	if (key == 77 || key == 109 || key == 220 || key == 252)
		menu(&obj_buff);
	//esc - выход
	if (key == 27)
		exit(0);
	if (obj_created) {
		obj_buff.back()->_image = t_image;
		points_buff.clear();
	}
	glutPostRedisplay();
}