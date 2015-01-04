#include <iostream>
#include <math.h>
#include "stdafx.h"

using namespace std;

class Point
{
public:
	Point(double xx, double yy)
	{ 
		x=xx; 
		y=yy; 
	}

	void Getxy();
	friend double Distance(Point &a, Point &b);

private:
	double x;
	double y;
};


void Point::Getxy()
{
	cout << "(" << x << "," << y << ")" << endl;
}


double Distance(Point &a, Point &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}


//void main1()
//{
//	Point p1(3.0, 4.0);
//	Point p2(6.0, 8.0);
//	p1.Getxy();
//	p2.Getxy();
//	double d = Distance(p1, p2);
//	cout << "Distance is" << d << endl;
//}

void main1()
{
	//cout << __FILE__ <<endl;
	cout << "Distance is" << endl;
}

