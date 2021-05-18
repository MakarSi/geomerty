#pragma once
#include "Point.h"
#include "vector.h"

class Segment: public Object
{
public:
	void set_v1(Point);
	void set_v2(Point);
	Point get_v1()const;
	Point get_v2()const;
	Segment(Point v1 = (0, 0), Point v2 = (0, 0));
	
	Segment operator+ (const Vector&);

	/*Нахождение координаты середины отрезка*/
	Point midpoint()const;
	//проверяем пересекаются ли два отрезка
	friend bool intersection(const Segment&, const Segment&);
	virtual void draw()const;
private:
	Point _v1, _v2;
};