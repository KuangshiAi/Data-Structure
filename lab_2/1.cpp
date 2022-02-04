#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct LIST
{
	int value;
	struct LIST* next;
	int status = 0;
}list;
list* loop(list* first)
{
	list* p = first;
	while (p->next&&!p->status)
	{
		p->status = 1;
		p = p->next;
	}
	if (p->status)
		return p;
	else
		return 0;
}
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
 int main()
{
	int length, point;
	printf("请输入链表的长度和环插入点的位置\n");
	scanf_s("%d%d", &length, &point);
	printf("将会生成一个链表值等于其位置（从1开始）的带环单链表\n");
	list* first = createlooplist(length, point);
	list* a = loop(first);
	printf("环插入点的值（也即位置）是%d", a->value);
	return 0;
}