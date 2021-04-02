#pragma once
#include "point.h"
#include "segment.h"
#include "polygon.h"
class Triangle : public polygon::Polygon {
public:
	//Êîíñòðóêòîð ïî 3 òî÷êàì
	Triangle(vector<Point> vertexes = {});
	~Triangle();

	/*Ïåðåãðóçêà îïåðàòîðà ðàâåíñòâà*/
	bool operator== (const Triangle& t) const;
	/*Ïåðåãðóçêà îïåðàòîðà íåðàâíåñòâà*/
	bool operator!= (const Triangle& t) const;

	//âñïîìîãàòåëüíûå ôóíêöèè
	//Ñðåäíÿÿ ëèíèÿ òðåóãîëüíèêà
	friend Segment middle_line(Triangle const &t);

private:
	Point _p1, _p2, _p3;
};