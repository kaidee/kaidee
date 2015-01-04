//

#include<iostream>
using namespace std;

/*
写两个函数，分别求两个整数的最大公约数和最小公倍数，
用主函数调用这两个函数，并输出结果，两个整数由键盘输入。
*/

//最大公约数
int divisor(int x, int y)
{
	int r, temp;
	if (x < y)
	{
		temp = x;
		x = y;
		y = temp;
	}
	while(x % y)
	{
		r = x % y;
		x = y;
		y = r;
	}
	return y;
}

//最小公倍数
int multiple(int x, int y, int d)
{
	return x*y/d;//两数相乘结果除以它们的最大公约数为最小公倍数
}

int main()
{	
	int x, y, d, m;
	cout << "input two numbers:";
	cin >> x >> y;
	d = divisor(x, y);
	m = multiple(x, y, d);
	cout << "common divisor is " << d << endl << "common multiple is "<<m;

	cout<<endl;
}