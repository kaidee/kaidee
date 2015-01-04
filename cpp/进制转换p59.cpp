#include <iostream>
#include<stdlib.h>
using namespace std;
typedef char ElemType;
#define StackSize 100
char str[100];
typedef struct 
{
	ElemType data[StackSize];
	int top;
}SqStack;

//1.初始化栈运算算法
void InitStack(SqStack &st)		
{
	st.top=-1;
}
int StackEmpty(SqStack st)
{
	if(st.top==-1)
		return 1;
	else
		return 0;
}
//2.进栈运算算法
int Push(SqStack &st,ElemType x)
{
	if (st.top==StackSize-1)
		return 0;
	else
	{
	st.top++;
	st.data[st.top]=x;
	return true;
	}
}

//3出栈运算算法
int Pop(SqStack &st,ElemType &x)
{
	if(st.top==-1)
		return false;
	else
	{
		
		x=st.data[st.top];
		st.top--;
		return 2;
	}
}
//6.

void Transform(int n,int r)
{
	SqStack st;
	char ch; int i=0;
	if(r<=1 || r>36 ||r==10)
	{	cout<<"待转换的进制错误！"<<endl;
		exit(1);
	}
	InitStack(st);
	while (n!=0)
	{
		ch=(char)(n%r);
		ch=ch+(ch<10?48:65-10);
		Push(st,ch);
		n/=r;
	}
	while(!StackEmpty(st))
	{
		Pop(st,ch);
		str[i++]=ch;
	}
	str[i]='\0';
}
void main()
{
	SqStack st;
	ElemType e;
	int i,j;
	cout<<"请输入需要转换的10进制数"<<endl;
	cin>>i;
	cout<<"请输入需要转换的进制（大于1小于36且不能等于10）"<<endl;
	cin>>j;
	Transform(i,j);
	cout<<"您所得到的"<<j<<"进制数为："<<endl;
	cout<<str<<endl;
}