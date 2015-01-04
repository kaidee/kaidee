//

#include<iostream>
using namespace std;

/*
 3、求Sn=a+aa+aaa+…+aa…a之值，其中a是一个数字。
 例如：2+22+222+…+22222（此时n=5），n由键盘输入。
*/

int main()
{	
	double a, sn=0.0, sum=0.0;
	int n;
	cout<<"input a:";
	cin>>a;
	cout<<"input n:";
	cin>>n;

	sn = a;
	sum = a;
	for (int i = 2; i <= n; ++i)
	{
		sum = sum*10 + a;
		sn += sum;
	}
	cout<<"sn = "<<sn<<endl;

	cout<<endl;
}