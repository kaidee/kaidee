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
	cout<<"������һ����Ҫ�жϵ�����\n";
	cin>>a;
	if(a==0)break;
	if(prime(a)==true)
	cout<<"������������������\n";
	else
		cout<<"�ⲻ��һ������\n";
	}
}
