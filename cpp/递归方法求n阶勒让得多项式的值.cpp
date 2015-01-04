//

#include<iostream>
using namespace std;

/*
 2、用递归方法求n阶勒让得多项式的值，递归公式为 
         1 (n = 0) 
Pn(x) =  x (n = 1) 
         ((2n-1)*x*Pn-1(x)-(n-1)*Pn-2(x))/n (n > 1) 
*/

double func(double n, double x)
{
	if (n == 0)
	{
		return 1;
	}
	else if (n == 1)
	{
		return x;
	}
	else if (n > 1)
	{
		return ((2*n-1)*x*func(n-1, x)-(n-1)*func(n-2,x))/n;
	}
}

int main()
{	
	double n, x, sum;
	cout<<"input n and x"<<endl;
	cin>>n>>x;
	sum = func(n, x);
	cout<<"P"<<n<<"("<<x<<")"<<"+"<<sum<<endl;

	cout<<endl;
}