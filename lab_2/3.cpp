#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxsize 100
char* substring(char* str, int position, int len)//position starts from 0
{
	char* result = (char*)calloc(len + 1, sizeof(char));
	for (int i = 0; i < len; i++)
		result[i] = str[position + i];
	return result;
}
int repeatjudge(char* str)
{
	int index[128] = { 0 };
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (index[str[i]])
			return 0;
		index[str[i]]++;
	}
	return len;
}
int main()
{
	char str[maxsize];
	printf("请输入待检测字符串\n");
	scanf_s("%s", str, maxsize);
	int len = strlen(str);
	int maxlength = 1;
	int i, j;
	for (i = 1; i <= len; i++)
		for (j = 0; j <= len - i; j++)
		{
			if (repeatjudge(substring(str, j, i)) > maxlength)
				maxlength = repeatjudge(substring(str, j, i));
		}
	printf("不含重复字符的最长子串长度为%d", maxlength);
	return 0;
}