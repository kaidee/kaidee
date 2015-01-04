//约瑟夫环

#include<iostream>
using namespace std;

/*

//约瑟夫环的实现：一群人围成一圈，这群人共有 n个人，每个人身上都一个key，依次给这圈人编号：
//1，2，n 一开始报数的上限值为m从第一个人（编号：1）自一开始报数报到m时停止报数，报到m的人出列，
//将他的密码做为新的m值，从他的顺时针方向开始的下个人开始从新从一报数，如此下去，直至所有的人出列为止 

*/

typedef struct node//节点存放一个数据和指向下一个节点的指针  
{  
    int data;  
    struct node* pnext;  
} Node;

Node *link_create(int n)//创建n个节点的循环链表  
{  
    //先创建第1个节点  
    Node *p,*q,*head;  
    int i ;  
    p = (Node *)malloc(sizeof(Node));  
    head = p;  
    p->data = 1;  
  
    for(i = 2;i<=n;i++)//再创建剩余节点  
    {  
        q = (Node *)malloc(sizeof(Node));  
        q->data = i;  
        p->pnext = q;  
        p = q;  
    }  
    p->pnext = head;//最后一个节点指向头部，形成循环链表  
    return head;  
}  
  
void link_process(Node *head,int k,int m)//从编号为k(1<=k<=n)的人开始报数，数到m的那个人出列；  
{  
    int i;  
    Node *p = head,*tmp1;  
    while(p->data != k)//p指向的节点data为k  
        p = p->pnext;  
      
    while(p->pnext != p)  
    {  
        for(i=1;i<m;i++)  
        {  
            tmp1 = p;  
            p = p->pnext;  
        }  
        printf("%d ->",p->data);  
        tmp1->pnext= p->pnext;  
        free(p);  
        p = tmp1->pnext;  
  
    }  
    printf("%d ",p->data);  
    free(p);  
}  
  
int main()  
{  
      
    Node *head = link_create(10);      
    link_process(head,3,3);  
    // system("pause");  
    cout<<endl;
    return 0;  
}  

// int main()
// {	
	

// 	cout<<endl;
// }