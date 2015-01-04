//

#include<iostream>
using namespace std;

/*

*/

int main()
{	
	double pi = 3.14;
	char *p = "hello world.";
	printf(p);
	char ch = *(char *)&pi;
	cout<<ch<<endl;
	char chh = (char)pi;
	cout<<chh<<endl;

	char chhh = static_cast<char>(pi);
	cout<<chhh<<endl;

	int a, b;
	// p = (a=1;b=2;b++;a+b;);
	cout<<(a=1,b=2,b++,a+b,a=32)<<endl;

	cout<<endl;
}

