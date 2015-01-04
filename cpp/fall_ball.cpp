//

#include<iostream>
using namespace std;

/*
4、一球从100米高度自由落下，
每次落地后反跳回原高度的一半，再落下。
求它在第10次落地时，共经过了多少米？第10次反弹多高？
*/

int main()
{	
	double h1=100, h2=100, sum=0.0;
	for (int i = 0; i < 10; ++i)
	{
		sum += h2;
		h1 /= 2.0;
		h2 = h1 * 2;
	}
	cout<<"sum="<<sum<<"  "<<"h1="<<h1<<endl;

	cout<<endl;
}