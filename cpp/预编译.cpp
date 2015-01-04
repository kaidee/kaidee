#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
//#define RUN
int main()
{
	int x=1,y=2,z=3;
#ifndef RUN
	cout<<"x="<<x<<",y="<<y<<",z="<<z<<endl;
#endif
	cout<<"x*y*z="<<x*y*z<<endl;
	return 0;
}