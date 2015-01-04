#include <iostream>       
typedef char ElemType;
typedef struct node
{
	ElemType data;					// 数据域
	struct node *next;				// 指针域
}SLink;

//1.1头插法建表
void CreateListF(SLink *&L1,ElemType a[],int n)
{
	SLink *s;int i;
	L1=(SLink *)malloc(sizeof(SLink));//创建头结点
	L1->next=NULL;
	for(i=0;i<n;i++)
	{
		s=(SLink *)malloc(sizeof(SLink));//创建新节点
		s->data=a[i];
		s->next=L1->next;
		L1->next=s;
	}
}

//1.2尾插法建表
void CreateListR(SLink *&L2,ElemType a[],int n)
{
	SLink *s,*r;int i;
	L2=(SLink *)malloc(sizeof(SLink));	//创建头结点
	L2->next=NULL;
	r=L2;
	for(i=0;i<n;i++)
	{
		s=(SLink *)malloc(sizeof(SLink));//新结点
		s->data=a[i];
		r->next=s;
		r=s;
	}
	r->next=NULL;						//尾结点next域置为NULL
}

//2.初始化线性表运算
void InitList(SLink *&L)
{
	L=(SLink *)malloc(sizeof(SLink));
	L->next=NULL;
}

//3.求线性表的长度运算
int GetLength(SLink *L)
{
	int i=0;
	SLink *p=L->next;
	while(p!=NULL)
	{
		i++;
		p=p->next;
	}
	return i;
}

//4.求线性表中第i个元素的运算
int GetElem(SLink *L,int i,ElemType &e)
{
	int j=1;
	SLink *p=L->next;
	if(i<1 || i>GetLength(L))
	return(0);
	while(j<1)
	{
		p=p->next;
		j++;
	}
	e=p->data;
	return(1);
}

//5.按值查找运算
int Locate(SLink *L,ElemType x)
{
	int i=1;
	SLink *p=L->next;
	while (p!=NULL && p->data!=x)
	{
		p=p->next;
		i++;
	}
	if(p==NULL)
		return(0);
	else
		return(i);
}

//6.插入结点运算
int InsElem(SLink *L,ElemType x,int i)
{
	int j=1;
	SLink *p=L,*s;
	s=(SLink *)malloc(sizeof(SLink));//创建data域为x的结点
	s->data=x;s->next=NULL;
	if(i<1 || i>GetLength(L)+1)
		return 0;
	while(j<i)
	{
		p=p->next;
		j++;
	}
	s->next=p->next;
	p->next=s;
	return 1;
}

//7.删除结点运算
int DelElem(SLink *L,int i)
{
	int j=1;
	SLink *p=L,*q;
	if(i<1 || i>GetLength(L))
		return 0;
	while(j<i)
	{
		p=p->next;
		j++;
	}
	q=p->next;
	p->next=q->next;
	free(q);
	return 1;
}

//8.输出线性表运算
void DispList(SLink *L)  //输出单链表
{
	SLink *p=L->next;
	while(p!=NULL)
	{
		printf("%c ",p->data);
		p=p->next;
	}
	printf("\n");
}

void main()
{
    
    int i;
    ElemType e;
    struct node *L;
    struct node *L1,*L2;
	ElemType a[5]={'a','b','c','d','e'},b[5]={'f','g','h','i','j'};
    InitList(L);					//初始化
    InsElem(L,'a',1);
    InsElem(L,'c',2);
    InsElem(L,'a',3);
    InsElem(L,'e',4);
    InsElem(L,'d',5);
    InsElem(L,'b',6);
    printf("线性表L：");DispList(L);
    printf("长度：%d\n",GetLength(L));
    i=3;GetElem(L,i,e);
    printf("第%d个元素：%c\n",i,e);
    e='a';
    printf("元素%c是第%d个元素\n",e,Locate(L,e));
    i=4;printf("删除第%d个元素\n",i);
    DelElem(L,i);
    printf("线性表：");DispList(L);   //
	CreateListF(L1,a,5);
    printf("线性表L1：");
    DispList(L1);
    CreateListR(L2,b,5);
    printf("线性表L2：");
    DispList(L2);
}