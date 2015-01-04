#include<iostream>
#include<iomanip>
using namespace std;
const int n=10;
const int m=4;
const int s=1;
void josephus(int a[n+1],int m,int s)
{
	int i,j,k,w,s1;
	for(i=1;i<=n;i++)
		a[i]=i;
	s1=s;
	for(i=n;i>=2;i--)
	{
		s1=(s1+m-1)%i;
		if(s1==0)
			s1=i;
		w=a[s1];
		for(j=s1;j<=i;j++)
			a[j]=a[j+1];
		a[i]=w;
	}
	for(k=n;k>=1;k--)
		cout<<a[k]<<setw(4);
	cout<<endl;
}
void main()
{
	//int n=50;
	int a[n+1];
	josephus( a, m,s);
}