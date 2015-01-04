//3.1.2栈的顺序存储及其基本运算

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

//1.初始化栈运算算法
void InitStack(SqStack &st)		//st为引用型参数
{
	st.top=-1;
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

//4.取栈顶元素运算算法
int GetTop(SqStack st,ElemType &x)
{
	if(st.top==-1)
		return 0;
	else
	{
		x=st.data[st.top];
		return 500;
	}
}
//5.判断栈空运算算法
int StackEmpty(SqStack st)
{
	if(st.top==-1)
		return 1;
	else
		return 0;
}
//6.
char str[100];
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
	//cout<<ch<<endl<<r;

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
	//InitStack(st);
	/*cout<<"栈"<<(StackEmpty(st)==1?"空":"不空")<<endl;
	cout<<"a进栈";Push(st,'a');cout<<endl;
	cout<<"b进栈";Push(st,'b');cout<<endl;
	cout<<"c进栈";Push(st,'c');cout<<endl;
	cout<<"d进栈";Push(st,'d');cout<<endl;
	cout<<"栈"<<(StackEmpty(st)==1?"空":"不空")<<endl;
	GetTop(st,e);
	cout<<"栈顶元素:"<<e<<endl;
	cout<<"出栈次序:";
	while(!StackEmpty(st))
	{
		Pop(st,e);
		cout<<e;
	}
	cout<<endl;*/
	
}
