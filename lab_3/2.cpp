#include<stdio.h>
#include<string.h>
#include"queue.h"
int main()
{
	printf("������Ҫ�����ַ���(���Ȳ�����40)\n");
	char str[40];
	scanf_s("%s", str, 40);
	Queue* q = new Queue(strlen(str));
	int frequency[128] = { 0 };
	for (int i = 0; i < strlen(str); i++)
	{
		if (frequency[str[i]] < 1)
		{
			frequency[str[i]]++;
			q->EnQueue(str[i]);
		}
		else
			frequency[str[i]]++;
	}
	char c;
	while (!q->isEmpty())
	{
		q->GetFront(c);
		if (frequency[c] <= 1)
			break;
		else
			q->DeQueue();
	}
	printf("��һ�����ظ��ַ���%c", c);
	return 0;
}