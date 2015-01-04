//水仙花数

#include<iostream>
using namespace std;

/*
打印出所有的“水仙花数”。所谓“水仙花数”是指一个三位数，其各位数字立方和等于该数本身。
例如，153是一水仙花数，因为153 = 13 + 53 + 33。
*/

int main()
{	
	int a=0, b=0, c=0, count = 10000;
	for (int i = 0; i < count; ++i)
	{
		a = i%10;
		b = i/10%10;
		c = i/100%10;
		if (a*a*a+b*b*b+c*c*c == i)
		{
			cout<<" i= " << i <<endl;
		}
	}
	cout<<endl;
}