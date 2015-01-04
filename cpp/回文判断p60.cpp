//������
#include <iostream>
#include<stdlib.h>
using namespace std;
typedef char ElemType;
#define StackSize 100
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
int IsPalindrome(char str[])
{
	int i=0;
	char ch,temp;
	SqStack st;
	InitStack(st);
	while((ch=str[i++])!='\0')
		Push(st,ch);
	i=0;
	while(!StackEmpty(st))
	{
		Pop(st,temp);
		if(temp!=str[i++])
			return 0;
	}
	return 1;
}


void main()
{
	//SqStack st;
	char str[1232];
	ElemType e;
	//string i;
	//cout<<"��������Ҫ�жϵ���"<<endl;
	//cin>>i;
	//cout<<"��������Ҫת���Ľ��ƣ�����1С��36�Ҳ��ܵ���10��"<<endl;
	//cin>>j;
	//IsPalindrome(char [12321]);
	if(IsPalindrome(str)==true)
	cout<<"����������ǻ�������"<<endl;
	else
		cout<<"��������ǻ�����";
	//cout<<str<<endl;
}