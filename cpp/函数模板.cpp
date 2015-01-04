#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
template<class T>
T max(T a,T b,T c)
{
	if(b>a)a=b;
	if(c>a)a=c;
	return a;
}
int main()
{
	int i1=123,i2=23,i3=-32,i;
	double d1=56.12,d2=85.32,d3=-123.321,d;
	i=max(i1,i2,i3);
	d=max(d1,d2,d3);
	cout<<"i_max="<<i<<endl;
	cout<<"d_max="<<d<<endl;
	return 0;
}