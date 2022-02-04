#include<stdio.h>
#include<string.h>
#include"queue.h"
int main()
{
	printf("请输入要检测的字符串(长度不超过40)\n");
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
	printf("第一个不重复字符是%c", c);
	return 0;
}