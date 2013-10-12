#include<iostream>
using namespace std;

void swap(int& m, int& n)
{
  int temp=m; m=n; n=temp;
}

int main(int argc, char const *argv[])
{
	int a=3, b=4;

	/* code */
	swap(a,b);
	cout<<"swaped a,b:"<<a<<b;
	return 0;
}