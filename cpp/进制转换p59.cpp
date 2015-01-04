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

//1.��ʼ��ջ�����㷨
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
//2.��ջ�����㷨
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

//3��ջ�����㷨
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
	{	cout<<"��ת���Ľ��ƴ���"<<endl;
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
	cout<<"��������Ҫת����10������"<<endl;
	cin>>i;
	cout<<"��������Ҫת���Ľ��ƣ�����1С��36�Ҳ��ܵ���10��"<<endl;
	cin>>j;
	Transform(i,j);
	cout<<"�����õ���"<<j<<"������Ϊ��"<<endl;
	cout<<str<<endl;
}