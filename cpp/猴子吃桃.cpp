//猴子吃桃问题

#include<iostream>
using namespace std;

/*
5、猴子吃桃问题。猴子第一天摘下若干个桃子，当即吃了一半，
还不过瘾，又多吃了一个。第二天早上又将剩下的桃子吃掉了一半，
又多吃了一个。以后每天早上都吃了前一天剩下的一半零一个。
到第10天早上想再吃时，见只剩一个桃子了。求第一天共摘了多少桃子。
*/

int main()
{	
	int number = 1;
	for (int i = 10; i > 1; --i)
	{
		number = (number + 1) * 2;
	}
	cout<<"number="<<number;

	cout<<endl;
}