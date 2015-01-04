//

#include<iostream>
using namespace std;

/*

写一函数用“气泡法”对输入的10个字符按由小到大的顺序排列。

*/

int main()
{	
	int temp, a[10];
	cout<<"input 10 numbers:"<<endl;
	for (int i = 0; i < 10; ++i)
	{
		cin>>a[i];
	}
	for (int i = 0; i < 10; ++i)
	{
		for (int j = i+1; j < 10; ++j)
		{
			if (a[i] > a[j])
			{
				temp = a[j];
				a[j] = a[i];
				a[i] = temp;
			}
		}
	}
	cout<<"result= ";
	for (int i = 0; i < 10; ++i)
	{
		cout<<a[i]<<" ";
	}

	cout<<endl;
}