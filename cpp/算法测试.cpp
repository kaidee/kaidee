#include<stdio.h>
int main()

{
	int a;
	int f;
loop:f=scanf("%d",&a);  //���������Ч��scanf�᷵��0
	if(!f)
	{
	fflush(stdin); //��ջ�����
         printf("error,input again:");
	goto loop;
	}
	if(a>0&&a<100)
		printf("Right!");
	else
		printf("error,input again:");
	goto loop;
}