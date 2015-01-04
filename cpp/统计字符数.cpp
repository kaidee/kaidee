//

#include<iostream>
using namespace std;

/*

3、编写一函数，由实参传来一字符串，统计此字符串中字母、
数字、空格、和其它字符的个数，并在主函数中输入字符串以及输出上述结果。

*/

void judge(char a[100])
{
	int letter=0, number=0, others=0, i=0;
	while (a[i] != '\0')
	{
		if ((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z'))
		{
			letter++;
		}
		else if (a[i]>='0'&&a[i]<='9')
		{
			number++;
		}
		else others++;
		i++;
	}
	cout<<"letter="<<letter<<" number="<<number<<" others="<<others;
}

int main()
{	
	const int size = 100;
	char a[size];
	cin.getline(a, size);
	judge(a);

	cout<<endl;
}