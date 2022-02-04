#include<stdio.h>
#include<iostream>
#include<vector>
using namespace std;
typedef struct node {
	int value;
	struct node* link;
}ListNode;
bool initialize(ListNode *&head,vector<int> a)
{
	int i;
	int n = a.size();
	if (!n)
		return false;
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	temp->value = a[0];
	temp->link = NULL;
	head = temp;
	ListNode* tail = temp;
	if (n == 1)
		return true;
	for (i = 1; i < n; i++)
	{
		ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
		temp->value = a[i];
		temp->link = NULL;
		tail->link = temp;
		tail = tail->link;
	}
	return true;
}
//这里采用了插入排序，时间复杂度o(n^2)，空间复杂度o(1)
ListNode* insertsort(ListNode* head)
{
	if (head == NULL || head->link == NULL)
		return head;
	ListNode* sorthead = head;
	ListNode* sorttail = head;
	ListNode* p = head->link;
	sorttail->link = NULL;
	while (p)
	{
		ListNode* sortp = sorthead;
		ListNode* pre = NULL;
		while (sortp&&sortp->value<=p->value)
		{
			pre = sortp;
			sortp = sortp->link;
		}
		if (pre==NULL)
		{
			ListNode* temp = p->link;
			p->link = sorthead;
			sorthead = p;
			p = temp;
		}
		else if (sortp==NULL)
		{
			sorttail->link = p;
			p = p->link;
			sorttail = sorttail->link;
			sorttail->link = NULL;
		}
		else
		{
			pre->link = p;
			p =p->link;
			pre->link->link = sortp;
		}
	}
	head = sorthead;
	return head;
}
void output(ListNode* head)
{
	if (head == NULL)
		return;
	ListNode* p = head;
	while (p)
	{
		printf("%d->", p->value);
		p = p->link;
	}
	printf("\b\b");
	printf("  ");
	printf("\n");
}
int main()
{
	vector<int>a = { 4,1,3,2 };
	ListNode* head=NULL;
	initialize(head, a);
	output(insertsort(head));
	return 0;
}