#include<iostream>
using namespace std;
double fac(int n)
{
	double f;
	if(n<0)
		cout<<"n<0,data error!"<<endl;
	else if(n==0) f=1;
	else f=fac(n-1)*n;
	return(f);
}
void main()
{
	double fac(int n);
	int n;
	double y;
	cout<<"Enter a positive intenger:";
	cin>>n;
	y=fac(n);
	cout<<n<<"!="<<y<<endl;
}