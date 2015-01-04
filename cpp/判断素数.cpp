#include<iostream>
using namespace std;
#include<math.h>
#include<iomanip>
bool prime(int i)
{
	int j;
	bool flag=true;
	for(j=2;j<=sqrt((double) i);j++)
	{
		if(i%j==0)
		{
			flag=false;
			break;
		}
		return flag;
	}
}
void main()
{
	while(1)
	{
	int a;
	cout<<"请输入一个需要判断的数：\n";
	cin>>a;
	if(a==0)break;
	if(prime(a)==true)
	cout<<"你输入的这个数是素数\n";
	else
		cout<<"这不是一个素数\n";
	}
}
