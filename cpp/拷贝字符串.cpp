//

#include<iostream>
using namespace std;

/*
编写一个程序，将字符数组s2中的全部字符拷贝到字符数组s1中。
不用strcpy函数。拷贝时，‘\0’也要拷贝过去。 ‘\0’后面的字符不拷贝。
*/

void scopy(char a[], char b[])
{
	int i;
	for (i = 0; b[i] != '\0'; ++i)
	{
		a[i] = b[i];
	}
	a[i] = '\0';
}

int main()
{	
	char s1[100];
	char s2[100] = "Hello World!";
	scopy(s1, s2);
	cout<<s1;

	cout<<endl;
}