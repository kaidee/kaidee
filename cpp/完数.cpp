//完数

#include<iostream>
using namespace std;

/*
一个数如果恰好等于它的因子之和，这个数就称为“完数”。
例如，6的因子为1、2、3，而6 = 1 + 2 + 3，因此6是“完数”。
*/

int main()
{	
	int count=10000, sum = 0, a[500], k, t;
	for (int i = 0; i < count; ++i)
	{
		k = 0;
		sum = 0;
		for (int j = 1; j < i; ++j)
		{
			if (i%j == 0)
			{
				sum += j;
				a[k++] = j;
			}
		}
		t = k;
		if (sum>0 && sum == i)
		{
			cout<<i<<"->";
			for (k = 0; k < t; ++k)
			{
				cout<<a[k];
				if (k<t-1)
				{
					cout<<",";
				}
			}
			cout<<endl;
		}
	}
	
	cout<<endl;
}