#include<stdio.h>
int main()

{
	int a;
	int f;
loop:f=scanf("%d",&a);  //如果输入无效，scanf会返回0
	if(!f)
	{
	fflush(stdin); //清空缓冲区
         printf("error,input again:");
	goto loop;
	}
	if(a>0&&a<100)
		printf("Right!");
	else
		printf("error,input again:");
	goto loop;
}