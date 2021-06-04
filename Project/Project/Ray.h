#pragma once
#include "vector.h"
#include "Point.h"
#include "Line.h"

using namespace std;

class Ray : public Object
{
public:
	/*Конструктор*/
	Ray(Point p = { 0, 0 }, Vector v = {1, 0});

	/*Сеттеры*/
	void set_point(Point p) {this->_p = p;}
	void set_vector(Vector v) {this->_v = v;}

	/*Геттеры*/
	Point get_point() const {return _p;}
	Vector get_vector() const {return _v;}

	/*Сдвиг луча на вектор*/
	Ray operator+ (const Vector& v);
	friend istream& operator>>(istream&, Ray&);

	/*Пересекаются ли два луча
	Первый луч преобразуется в прямую, переходи к задаче поиска пересечения луча и прямой
	Алгоритм нахождения по ссылке: https://www.interestprograms.ru/source-codes-peresechenie-lucha-i-pryamoj*/
	friend bool intersection_ray_ray(const Ray& r1, const Ray& r2);
	/*Есть ли пересечение между лучами*/
	friend bool intersection_point_existence(const Ray& r1, const Ray& r2);
	//Возвращает точку пересечения лучей. Если её нет, то возвращает точку (INT_MAX, INT_MAX)
	friend Point ray_intersection_point(const Ray& r1, const Ray& r2);
	//Возвращает угол между лучами
	friend double angle_between_rays(const Ray& r1, const Ray& r2);
	/*Рисование*/
	virtual void draw()const;
	/*Печать информации об луче - начало (точка) и направляющий вектор*/
	virtual void print_info()const;
private:
	Point _p; Vector _v;
};
bool intersection_ray_ray(const Ray& r1, const Ray& r2);
bool intersection_point_existence(const Ray& r1, const Ray& r2);
Point ray_intersection_point(const Ray& r1, const Ray& r2);
double angle_between_rays(const Ray& r1, const Ray& r2);