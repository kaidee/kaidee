#include "stdafx.h"

using namespace std;

// ´úÂëÆ¬¶Î1
//#include <iostream.h>

//class M
//{
//public:
//	M() { x=y=0; }
//	M(int i, int j) { x=i; y=j; }
//	void copy(M *m);
//	void setxy(int i, int j) { x=i; y=j; }
//	void print() { cout<<x<<","<<y<<endl; }
//private:
//	int x, y;
//};
//
//void M::copy(M *m)
//{
//	x=m->x;
//	y=m->y;
//}
//
//void fun(M m1, M *m2);
//
//void fun(M m1, M *m2)
//{
//	m1.setxy(12, 15);
//	m2->setxy(22,25);
//}
//
//void main()
//{
//	M p(5, 7), q;
//	p.print();
//	q.print();
//	cout<<"----------"<<endl;
//	q.copy(&p);
//	p.print();
//	q.print();
//	cout<<"----------"<<endl;
//	fun(p, &q);
//	p.print();
//	q.print();
//}


// ´úÂëÆ¬¶Î2
//#include <iostream.h>

class M
{
public:
	M() { x=y=0; }
	M(int i, int j) { x=i; y=j; }
	void copy(M &m);
	void setxy(int i, int j) { x=i; y=j; }
	void print() {cout<<x<<","<<y<<endl; }
private:
	int x, y;
};

void M::copy(M &m)
{
	x=m.x;
	x=m.y;
}

void fun(M m1, M &m2);

//void main()
//{
//	M p(5, 7), q;
//	q.copy(p);
//	fun(p, q);
//	p.print();
//	q.print();
//}
void fun(M m1, M &m2)
{
	m1.setxy(12, 15);
	m2.setxy(22, 25);
}



