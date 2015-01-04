//链表

#include<iostream>
using namespace std;

/*

链表的一些操作

*/

struct ListNode
{
	int m_nKey;
	ListNode *m_pNext;
};

// 求单链表中结点的个数
unsigned int GetListLength(ListNode* pHead)
{
	if (pHead == NULL)
	{
		return 0;
	}
	unsigned int nLength = 0;
	ListNode* pCurrent = pHead;
	while(pCurrent != pHead)
	{
		nLength++;
		pCurrent = pCurrent->m_pNext;
	}
	return nLength;
}

// 反转单链表
ListNode* ReverseList(ListNode* pHead)
{
	// 如果链表为空或只有一个结点
	if (ph  == NULL || pHead->m_pNext == NULL)
	{
		return pHead;
	}

	ListNode* pReversedHead = NULL; //新链表
	ListNode* pCurrent = pHead;
	while(pCurrent != NULL)
	{
		ListNode* pTemp = pCurrent;
		pCurrent = pCurrent->m_pNext;
		pTemp->m_pNext = pReversedHead;
		pReversedHead = pTemp;
	}
	return pReversedHead;
}

// 查找单链表中倒数第K个结点
ListNode * RGetKthNode(ListNode * pHead, unsigned int k) // 函数名前面的R代表反向
{
	if(k == 0 || pHead == NULL) // 这里k的计数是从1开始的，若k为0或链表为空返回NULL
		return NULL;

	ListNode * pAhead = pHead;
	ListNode * pBehind = pHead;
	while(k > 1 && pAhead != NULL) // 前面的指针先走到正向第k个结点
	{
		pAhead = pAhead->m_pNext;
		k--;
	}
	if(k > 1 || pAhead == NULL)     // 结点个数小于k，返回NULL
		return NULL;
	while(pAhead->m_pNext != NULL)  // 前后两个指针一起向前走，直到前面的指针指向最后一个结点
	{
		pBehind = pBehind->m_pNext;
		pAhead = pAhead->m_pNext;
	}
	return pBehind;  // 后面的指针所指结点就是倒数第k个结点
}

int main()
{	
	

	cout<<endl;
}