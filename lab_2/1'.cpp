#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct LIST
{
	int value;
	struct LIST* next;
}list;
list* createlooplist(int length, int point)
{
	list* first = new list;
	first->value = 1;
	list* tail = first;
	for (int i = 2; i <= length; i++)
	{
		list* p = new list;
		p->value = i;
		tail->next = p;
		tail = tail->next;
	}
	list* q = first;
	for (int i = 1; i < point; i++)
	{
		q = q->next;
	}
	tail->next = q;
	return first;
}
list* loop(list* first)
{
	list* fast, *slow;
	fast = slow = first;
	while (slow != NULL && fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			break;
	}
	if (slow == NULL || fast->next == NULL)
		return NULL;
	list* p1=first, * p2=slow;
	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}
int main()
{
	int length, point;
	printf("����������ĳ��Ⱥͻ�������λ��\n");
	scanf_s("%d%d", &length, &point);
	printf("��������һ������ֵ������λ�ã���1��ʼ���Ĵ���������\n");
	list* first = createlooplist(length, point);
	list* a = loop(first);
	printf("��������ֵ��Ҳ��λ�ã���%d", a->value);
	return 0;
}