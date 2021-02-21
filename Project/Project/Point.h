#pragma once
class Point
{
public: 
	Point(double x = 0, double y = 0);
	double GetX();
	void SetX(double);
	double GetY();
	void SetY(double);
	void PrintCoordinate();
	bool operator== (const Point& a);
	bool operator!= (const Point& a);
	Point operator+ (const Point& a);
	Point operator- (const Point& a);
	//friend ostream operator<<(ostream & out,const Point& a);
private: 
	double _x, _y;
};
double Distance(Point a, Point b);

